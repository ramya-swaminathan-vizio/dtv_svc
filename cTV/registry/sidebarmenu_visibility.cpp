// Copyright (C) 2021 VIZIO, Inc.  All rights reserved.
//
#include "sidebarmenu_visibility.h"

#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

#include <broker.h>
#include <connection.h>
#include <systemregistry.h>

const std::string _srServerName = "SystemRegistry";

template<typename TReply, typename TRequest> std::unique_ptr<TReply> sendMessage(std::unique_ptr<ipc::Connection> & channel, const TRequest & message, const std::string & id)
{
  ipc::SerializableMessage<TRequest> request(message);
  auto sent = channel->send(request, id);
  if (sent)
  {
    auto reply = channel->receiveSerialized<TReply>(id);
    if(reply.second)
      return std::make_unique<TReply>(*reply.first);
  }
  return nullptr;
}

std::string toString(MenuUIState state)
{
  switch (state)
  {
    case MenuUIState::MenuUIStateVisible:
      return "Visible";
    case MenuUIState::MenuUIStateInvisible:
      return "Invisible";
    case MenuUIState::MenuUIStateUnknown:
      return "Unknown";
    default:
      return "NotMenuUIState";
  }
}

bool updateSysRegMenuUIState(std::unique_ptr<ipc::Connection>& connectionToServer, std::string& state)
{
  if (state.empty())
  {
    std::cout << "Call method with illegal parameters" << std::endl;
    return false;
  }

  SysRegUpdateRequest request("/sidebarmenu/visibility", state);
  auto response = sendMessage<SysRegUpdateResponse>(connectionToServer, request, SYSREG_CMD_ID_UPDATE);

  if (!response || (response && response->status != SYSREG_RESULT_SUCCESS))
  {
    std::cout << "Failed to update state" << std::endl;
    return false;
  }
  std::cout << "MenuUIState Update Success" << std::endl;
  return true;
}

bool createSysRegMenuUIState(std::unique_ptr<ipc::Connection>& connectionToServer)
{
  SysRegCreateRequest requests[] {
      {"/sidebarmenu",               ""},
      {"/sidebarmenu/visibility",    "NotMenuUIState", SYSREG_FLAG_TMP_STORAGE}
  };

  for (auto & req : requests) {
      auto reply = sendMessage<SysRegCreateResponse>(connectionToServer, req, SYSREG_CMD_ID_CREATE);
      if (!reply || (reply->status != SYSREG_RESULT_SUCCESS && reply->status != SYSREG_RESULT_EXIST)) {
        std::cout << "Failed to create state" << std::endl;
        return false;
      }
  }
  std::cout << "Success to create MenuUIState" << std::endl;
  return true;
}

struct _MenuUIStateServer
{
  static bool initialize()
  {
    std::cout << "Initialize MenuUIState started..." << std::endl;
    if (nullptr == _connection)
      _connection = ipc::Broker::getDefaultBroker().connectToServer(_srServerName);

    if (_connection && !_createdSRMS)
    {
      _createdSRMS = createSysRegMenuUIState(_connection);
      if (_createdSRMS)
        _initialized = true;
    }
    std::cout << "Initialize MenuUIState ended!" << std::endl;
    return _initialized;
  }

  static std::unique_ptr<ipc::Connection> _connection;
  static std::atomic<bool> _initialized;
  static std::atomic<bool> _createdSRMS;
  static MenuUIState _previous;
};
std::unique_ptr<ipc::Connection> _MenuUIStateServer::_connection{nullptr};
std::atomic<bool> _MenuUIStateServer::_initialized{false};
std::atomic<bool> _MenuUIStateServer::_createdSRMS{false};
MenuUIState _MenuUIStateServer::_previous{MenuUIState::MenuUIStateUnknown};

bool initializeMenuUIState()
{
  if (!_MenuUIStateServer::_initialized)
  {
    if (!_MenuUIStateServer::initialize())
    {
      std::cout << "Cannot initialize() MenuUIState" << std::endl;
      return false;
    }
    std::cout << "initialize() Successfully MenuUIState" << std::endl;
  }
  else
  {
    std::cout << "initialize() MenuUIState is already initialized" << std::endl;
  }
  return true;
}

void setMenuUIState(MenuUIState state)
{
  if (state == _MenuUIStateServer::_previous)
    return;

  _MenuUIStateServer::_previous = state;

  if (!_MenuUIStateServer::_initialized)
  {
    std::cout << "Calling 'setMenuUIState' before 'initialize' is not allowed" << std::endl;
    return;
  }

  std::string visibility = toString(state);
  if ("NotMenuUIState" == visibility)
  {
    std::cout << "Unrecognized  MenuUIState" << std::endl;
    return;
  }
  updateSysRegMenuUIState(_MenuUIStateServer::_connection, visibility);
}

void deinitializeMenuUIState()
{
  std::cout << "Deinitialize MenuUIState started..." << std::endl;
  if (!_MenuUIStateServer::_initialized)
  {
    std::cout << "MenuUIState was not initialized" << std::endl;
  }
  std::cout << "Deinitialize  MenuUIState ended!" << std::endl;
}
