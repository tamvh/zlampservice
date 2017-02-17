/* 
 * File:   WebSocketRequestHandler.h
 * Author: tamvh
 *
 * Created on December 28, 2015, 4:37 PM
 */

#ifndef WEBSOCKETREQUESTHANDLER_H
#define WEBSOCKETREQUESTHANDLER_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>
#include <map>
#include <mutex>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>

#include "ClientInfo.h"
#include "WebSocketMessage.h"
#include "ServerPacket.h"
#include <zapiws/ZApiWS.h>

class WebSocketRequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    WebSocketRequestHandler();
    WebSocketRequestHandler(std::shared_ptr<ZApiWS> test_srv);
    virtual ~WebSocketRequestHandler();
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);  
private:   
    std::shared_ptr<ZApiWS> ws_server;
};

#endif /* WEBSOCKETREQUESTHANDLER_H */

