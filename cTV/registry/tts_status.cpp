// Copyright (C) 2021 VIZIO, Inc.  All rights reserved.
//
#include "tts_status.h"

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

std::string kTtsStatusOnStr = "ON";
std::string kTtsStatusOffStr = "OFF";
std::string kTtsStatusUnknownStr = "UNKNOWN";

std::string toString(TtsStatus state)
{
  switch (state)
  {
    case TtsStatus::TtsStatusOn:
      return kTtsStatusOnStr;
    case TtsStatus::TtsStatusOff:
      return kTtsStatusOffStr;
    case TtsStatus::TtsStatusUnknown:
      return kTtsStatusUnknownStr;
    default:
      return "NotTtsStatus";
  }
}

bool updateSysRegTtsStatus(std::unique_ptr<ipc::Connection>& connectionToServer, std::string& state)
{
  if (state.empty())
  {
    std::cout << "Call method with illegal parameters" << std::endl;
    return false;
  }

  SysRegUpdateRequest request("/current/tts", state);
  auto response = sendMessage<SysRegUpdateResponse>(connectionToServer, request, SYSREG_CMD_ID_UPDATE);

  if (!response || (response && response->status != SYSREG_RESULT_SUCCESS))
  {
    std::cout << "Failed to update state" << std::endl;
    return false;
  }
  std::cout << "TtsStatus Update Success" << std::endl;
  return true;
}

bool createSysRegTtsStatus(std::unique_ptr<ipc::Connection>& connectionToServer)
{
  SysRegCreateRequest requests[] {
      {"/current",     ""},
      {"/current/tts", kTtsStatusOffStr, SYSREG_FLAG_TMP_STORAGE}
  };

  for (auto & req : requests) {
      auto reply = sendMessage<SysRegCreateResponse>(connectionToServer, req, SYSREG_CMD_ID_CREATE);
      if (!reply || (reply->status != SYSREG_RESULT_SUCCESS && reply->status != SYSREG_RESULT_EXIST)) {
        std::cout << "Failed to create state" << std::endl;
        return false;
      }
  }
  std::cout << "Success to create TtsStatus" << std::endl;
  return true;
}

struct _ttsStatusServer
{
  static bool initialize()
  {
    std::cout << "Initialize TtsStatus started..." << std::endl;
    if (nullptr == _connection)
      _connection = ipc::Broker::getDefaultBroker().connectToServer(_srServerName);

    if (_connection && !_createdSRMS)
    {
      _createdSRMS = createSysRegTtsStatus(_connection);
      if (_createdSRMS)
        _initialized = true;
    }
    std::cout << "Initialize TtsStatus ended!" << std::endl;
    return _initialized;
  }

  static std::unique_ptr<ipc::Connection> _connection;
  static std::atomic<bool> _initialized;
  static std::atomic<bool> _createdSRMS;
  static TtsStatus _previous;
};
std::unique_ptr<ipc::Connection> _ttsStatusServer::_connection{nullptr};
std::atomic<bool> _ttsStatusServer::_initialized{false};
std::atomic<bool> _ttsStatusServer::_createdSRMS{false};
TtsStatus _ttsStatusServer::_previous{TtsStatus::TtsStatusUnknown};

bool initializeTtsStatus()
{
  if (!_ttsStatusServer::_initialized)
  {
    if (!_ttsStatusServer::initialize())
    {
      std::cout << "Cannot initialize() TtsStatus" << std::endl;
      return false;
    }
    std::cout << "initialize() Successfully TtsStatus" << std::endl;
  }
  else
  {
    std::cout << "initialize() TtsStatus is already initialized" << std::endl;
  }
  return true;
}

void setTtsStatus(TtsStatus state)
{
  if (state == _ttsStatusServer::_previous)
    return;

  _ttsStatusServer::_previous = state;

  if (!_ttsStatusServer::_initialized)
  {
    std::cout << "Calling 'setTtsStatus' before 'initialize' is not allowed" << std::endl;
    return;
  }

  std::string onOff = toString(state);
  if ("NotTtsStatus" == onOff)
  {
    std::cout << "Unrecognized  TtsStatus" << std::endl;
    return;
  }
  updateSysRegTtsStatus(_ttsStatusServer::_connection, onOff);
}

void deinitializeTtsStatus()
{
  std::cout << "Deinitialize TtsStatus started..." << std::endl;
  if (!_ttsStatusServer::_initialized)
  {
    std::cout << "TtsStatus was not initialized" << std::endl;
  }
  std::cout << "Deinitialize  TtsStatus ended!" << std::endl;
}
