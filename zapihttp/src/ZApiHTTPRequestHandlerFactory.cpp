/*
 * File:   ZApiHTTPRequestHandlerFactory.cpp
 * Author: huuhoa
 *
 * Created on October 27, 2015, 11:35 AM
 */

#include <Poco/Util/Application.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/RegularExpression.h>

#include "TimeRequestHandler.h"
#include "VersionRequestHandler.h"
#include "zapihttp/ZApiHTTPLampMachineRequestHandler.h"
#include "zapihttp/ZApiHTTP.h"

#include "ZApiHTTPRequestHandlerFactory.h"

using Poco::Util::Application;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPRequestHandler;
using Poco::RegularExpression;

HTTPRequestHandler* ZApiHTTPRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request) {
    const std::string& requestURI = request.getURI();

    Application& app = Application::instance();
    app.logger().information("Request URI " + requestURI);
    if (requestURI.compare(0, _apiPrefix.length(), _apiPrefix) == 0) {
        std::string path = requestURI.substr(_apiPrefix.length());

        if (path == "/version") {
            return new VersionRequestHandler();
        }
               
        
        if (ZApiHTTPLampMachineRequestHandler::CanHandleRequest(path, request.getMethod())) {
            return new ZApiHTTPLampMachineRequestHandler(path, _api);
        }                
    }

    if (requestURI == "/time") {
        return new TimeRequestHandler(_format);
    } else if (requestURI == "/version") {
        return new VersionRequestHandler();
    } else {
        return 0;
    }
}
