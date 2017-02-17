/*
 * File:   RequestHandlerFactory.cpp
 * Author: tamvh
 *
 * Created on December 28, 2015, 4:39 PM
 */

#include "WebSocketRequestHandler.h"
#include "PageRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "zapiws/ZApiWS.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::Application;

RequestHandlerFactory::RequestHandlerFactory() {
}

RequestHandlerFactory::RequestHandlerFactory(std::shared_ptr<ZApiWS> server) {
    ws_server = server;
}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    Application& app = Application::instance();
    app.logger().information("Request from "
            + request.clientAddress().toString()
            + ": "
            + request.getMethod()
            + " "
            + request.getURI()
            + " "
            + request.getVersion());
    for (Poco::Net::HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it) {
        app.logger().information(it->first + ": " + it->second);
    }



    if (request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0) {
        return new WebSocketRequestHandler(ws_server);
    } else
        return new PageRequestHandler;
}


