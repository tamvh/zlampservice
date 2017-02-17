/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZApiHTTPCoffeeMachineRequestHandler.cpp
 * Author: tamvh
 * 
 * Created on April 13, 2016, 10:26 AM
 */
#include <stdlib.h>
#include <stdint.h>
#include <sstream>
#include <fcntl.h>

#include <Poco/RegularExpression.h>
#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Struct.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/NumberParser.h>

#include <zcommon/ZServiceLocator.h>
#include <zsession/ZSessionService.h>
#include <zworker/ZWorker.h>
#include <zapihttp/ZApiHTTP.h>
#include "zapihttp/ZApiHTTPLampMachineRequestHandler.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::DynamicStruct;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::Application;

void ReportError::reportTo(HttpApiError error, Poco::JSON::Object::Ptr& responseData) {
    responseData->set("error", static_cast<int> (error));
}

ZApiHTTPLampMachineRequestHandler::ZApiHTTPLampMachineRequestHandler(const std::string& path, std::shared_ptr<ZApiHTTP> ws_server) :
ZApiHTTPRequestBaseHandler(path) {
    _ws_server = ws_server;
}

ZApiHTTPLampMachineRequestHandler::~ZApiHTTPLampMachineRequestHandler() {
}

bool ZApiHTTPLampMachineRequestHandler::CanHandleRequest(const std::string& path, const std::string& method) {
    if (path.compare("/lamp/choose") == 0 && method.compare("POST") == 0) {
        return true;
    }
    if (path.compare("/lamp/stt") == 0 && method.compare("GET") == 0) {
        return true;
    }
    return false;
}

void ZApiHTTPLampMachineRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;
    const std::string& method = request.getMethod();

    if (requestPath().compare("/lamp/choose") == 0) {
        if (method.compare("POST") == 0) {
            handleChangeStatus(request, responseData);
        }
    }
    if (requestPath().compare("/lamp/stt") == 0) {
        if (method.compare("GET") == 0) {
            handleGetStatus(request, responseData);
        }
    }
    std::ostream& ostr = response.send();
    Poco::JSON::Stringifier::stringify(responseData, ostr);
}

void ZApiHTTPLampMachineRequestHandler::handleChangeStatus(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {

    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    try {
        Var result = parseServerRequest(request, responseData);
        if (result.isEmpty()) {
            return;
        }
        Object::Ptr object = result.extract<Object::Ptr>();
        std::string lamp = object->optValue("type", std::string());   
        _ws_server->writeserial(lamp);
        if (lamp.empty()) {
            ReportError::reportTo(HttpApiError::ParameterMissing, responseData);
            return;
        }
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return;
    }
}
void ZApiHTTPLampMachineRequestHandler::handleGetStatus(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {

    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    try {
//        Var result = parseServerRequest(request, responseData);
//        if (result.isEmpty()) {
//            return;
//        }
//        Object::Ptr object = result.extract<Object::Ptr>();
//        std::string lamp = object->optValue("type", std::string());   
//        
//        if (lamp.empty()) {
//            ReportError::reportTo(HttpApiError::ParameterMissing, responseData);
//            return;
//        }
//        _ws_server->writeserial(lamp);
        fillterSTT(_ws_server->getSTTLamp1(), _ws_server->getSTTLamp2(),responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return;
    }
}

void ZApiHTTPLampMachineRequestHandler::fillterSTT(
        const std::string &sttLamp1, 
        const std::string &sttLamp2, 
        Poco::JSON::Object::Ptr & responseData){
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    responseData->set("Lamp1", sttLamp1);
    responseData->set("Lamp2", sttLamp2);
}

