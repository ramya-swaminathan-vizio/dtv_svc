// Copyright (C) 2021 VIZIO, Inc.  All rights reserved.
//
#include "store_demo_status.h"

#include <string>
#include <thread>

#include <broker.h>
#include <connection.h>
#include <systemregistry.h>

namespace {

const auto kStoreDemoStatus = "/current/store-demo-status";
const auto kTimeout = std::chrono::milliseconds(20);

template<typename TReply, typename TRequest>
std::unique_ptr<TReply>
sendMessage(const std::unique_ptr<vizio::ipc::Connection>& connection,
            const TRequest& message,
            const std::string& id)
{
    size_t subtopic = std::hash<std::thread::id>()(std::this_thread::get_id());
    vizio::ipc::SerializableMessage<TRequest> request(message);
    request.subTopic(subtopic);

    std::string rxTopic = id + ":" + std::to_string(subtopic); // mandatory to follow such format

    auto sent = connection->send(request, id, false); // false means don't block if queue if full
    if (sent)
    {
        auto reply = connection->receiveSerialized<TReply>(rxTopic, kTimeout);
        if (reply.second)
        {
            return std::make_unique<TReply>(*reply.first);
        }
        // log the failure to receive the message
        return nullptr;
    }
    else
    {
        // log the failure to send the message
    }
    return nullptr;
}

std::string toString(NAV_RETAIL_MODE_STATUS_T status)
{
    switch (status)
    {
        case NAV_RETAIL_MODE_INITIAL:    return "initial";
        case NAV_RETAIL_MODE_LAUNCHING:  return "launching";
        case NAV_RETAIL_MODE_CHECKING:   return "checking";
        case NAV_RETAIL_MODE_RUNNING:    return "running";
        case NAV_RETAIL_MODE_PAUSE:      return "pause";
        case NAV_RETAIL_MODE_EXIT:       return "exit";
        case NAV_RETAIL_MODE_RESTARTING: return "restarting";
        case NAV_RETAIL_MODE_ERROR:      return "error";
        default: return "unknown";
    }
}

bool storeDemoStatusExists(const std::unique_ptr<vizio::ipc::Connection>& connection)
{
    SysRegGetRequest request(kStoreDemoStatus);
    auto reply = sendMessage<SysRegGetResponse>(connection, request, SYSREG_CMD_ID_GET);
    return reply && reply->status == SYSREG_RESULT_SUCCESS;
}

bool updateSysRegStoreDemoStatus(const std::unique_ptr<vizio::ipc::Connection>& connection,
                                 const std::string& state)
{
    if (state.empty())
    {
        return false;
    }

    SysRegUpdateRequest request(kStoreDemoStatus, state);
    auto response = sendMessage<SysRegUpdateResponse>(connection, request, SYSREG_CMD_ID_UPDATE);

    if (!response || (response && response->status != SYSREG_RESULT_SUCCESS))
    {
        return false;
    }
    return true;
}

bool createSysRegStoreDemoStatus(const std::unique_ptr<vizio::ipc::Connection>& connection)
{
    SysRegCreateRequest requests[]
    {
        {"/current",       ""},
        {kStoreDemoStatus, "initial", SYSREG_FLAG_TMP_STORAGE}
    };

    for (auto& req : requests)
    {
        auto reply = sendMessage<SysRegCreateResponse>(connection, req, SYSREG_CMD_ID_CREATE);
        if (!reply || (reply->status != SYSREG_RESULT_SUCCESS && reply->status != SYSREG_RESULT_EXIST))
        {
            return false;
        }
    }
    return true;
}

} // anonymous namespace

void setStoreDemoStatus(NAV_RETAIL_MODE_STATUS_T mode)
{
    const auto connection = vizio::ipc::Broker::getDefaultBroker().connectToServer("SystemRegistry");
    if (connection)
    {
        if (!storeDemoStatusExists(connection))
        {
            createSysRegStoreDemoStatus(connection);
        }
        updateSysRegStoreDemoStatus(connection, toString(mode));
    }
}
