/*
 * File:   ZApiWS.cpp
 * Author: tamhuy
 *
 * Created on October 24, 2015, 3:19 PM
 */

#include <Poco/Delegate.h>
#include <Poco/Util/Application.h>

#include <zcommon/ZServiceLocator.h>
#include <zworker/ZWorker.h>

#include "RequestHandlerFactory.h"
#include "ServerPacket.h"
#include "WebSocketMessage.h"
#include "ServerPacket.h"

#include "zapiws/ZApiWS.h"

using Poco::Util::Application;
void ZApiWS::onDeviceDataUpdated(const void *pSender, const ZDeviceDataUpdatedEvent &event) {
//    Application& app = Application::instance();
//    Poco::JSON::Array::Ptr params = new Poco::JSON::Array;
//    Poco::JSON::Object::Ptr item = new Poco::JSON::Object;
//    item->set("varId", event.varialbleId());
//    item->set("value", event.varialbleValue());
//    params->add(item);
//
//    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;
//    Poco::JSON::Object::Ptr data = new Poco::JSON::Object;
//
//    data->set("deviceid", event.device()->info()->deviceId());
//    data->set("name", event.device()->info()->deviceName());
//    data->set("group", event.device()->info()->deviceGroup());
//    data->set("type", event.device()->info()->deviceType());
//    data->set("apikey", event.device()->info()->apiKey());
//    data->set("createdAt", static_cast<Poco::Int64> (event.device()->info()->createdAt()));
//    data->set("lastModified", static_cast<Poco::Int64> (event.device()->info()->updatedAt()));
//    data->set("params", params);
//
//    responseData->set("action", "update");
//    responseData->set("data", data);
//
//    std::stringstream buffer;
//    Poco::JSON::Stringifier::stringify(responseData, buffer);
//    app.logger().information("data update: " + buffer.str());
//    std::string userApiKey = event.userApiKey();
//    send_client_list(userApiKey, buffer.str());
}

void ZApiWS::onDeviceDataCreated(const void *pSender, const ZDeviceDataCreatedEvent &event) {
//    Poco::JSON::Array::Ptr params = new Poco::JSON::Array;
//    Poco::JSON::Object::Ptr item = new Poco::JSON::Object;
//    item->set("varId", event.varialbleId());
//    item->set("value", event.varialbleValue());
//    params->add(item);
//
//    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;
//    Poco::JSON::Object::Ptr data = new Poco::JSON::Object;
//
//
//    data->set("deviceid", event.device()->info()->deviceId());
//    data->set("name", event.device()->info()->deviceName());
//    data->set("group", event.device()->info()->deviceGroup());
//    data->set("type", event.device()->info()->deviceType());
//    data->set("apikey", event.device()->info()->apiKey());
//    data->set("createdAt", static_cast<Poco::Int64> (event.device()->info()->createdAt()));
//    data->set("lastModified", static_cast<Poco::Int64> (event.device()->info()->updatedAt()));
//    data->set("params", params);
//
//    responseData->set("action", "create");
//    responseData->set("data", data);
//
//    std::stringstream buffer;
//    Poco::JSON::Stringifier::stringify(responseData, buffer);
//    
//    send_client_list(event.device()->info()->apiKey(), buffer.str());
    
}

void ZApiWS::onDeviceDeletedDevice(const void *pSender, const ZDeviceDataDeletedEvent &event) {
//    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;
//    Poco::JSON::Object::Ptr data = new Poco::JSON::Object;
//
//    data->set("deviceid", event.deviceId());
//
//    responseData->set("action", "delete");
//    responseData->set("data", data);
//
//    std::stringstream buffer;
//    Poco::JSON::Stringifier::stringify(responseData, buffer);
//
//    send_client_list(event.apiKey(), buffer.str());
}

void ZApiWS::onDeviceChangedDeviceInformation(const void *pSender, const ZDeviceDataChangeInformationEvent &event) {
//    Poco::JSON::Array::Ptr params = new Poco::JSON::Array;
//    Poco::JSON::Object::Ptr item = new Poco::JSON::Object;
//    item->set("varId", event.varialbleId());
//    item->set("value", event.varialbleValue());
//    params->add(item);
//
//    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;
//    Poco::JSON::Object::Ptr data = new Poco::JSON::Object;
//
//
//    data->set("deviceid", event.device()->info()->deviceId());
//    data->set("name", event.device()->info()->deviceName());
//    data->set("group", event.device()->info()->deviceGroup());
//    data->set("type", event.device()->info()->deviceType());
//    data->set("apikey", event.device()->info()->apiKey());
//    data->set("createdAt", static_cast<Poco::Int64> (event.device()->info()->createdAt()));
//    data->set("lastModified", static_cast<Poco::Int64> (event.device()->info()->updatedAt()));
//    data->set("params", params);
//
//    responseData->set("action", "updateinfo");
//    responseData->set("data", data);
//
//    std::stringstream buffer;
//    Poco::JSON::Stringifier::stringify(responseData, buffer);
//    send_client_list(event.device()->info()->apiKey(), buffer.str());
}
