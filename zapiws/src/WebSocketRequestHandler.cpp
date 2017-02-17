/*
 * File:   WebSocketRequestHandler.cpp
 * Author: tamvh
 *
 * Created on December 28, 2015, 4:37 PM
 */
#include "WebSocketRequestHandler.h"

using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Util::ServerApplication;
using Poco::Util::Application;

WebSocketRequestHandler::WebSocketRequestHandler() {
}

WebSocketRequestHandler::WebSocketRequestHandler(std::shared_ptr<ZApiWS> server)
{
    ws_server = server;
}

WebSocketRequestHandler::~WebSocketRequestHandler() {
}

void WebSocketRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
    Application& app = Application::instance();    
    try {
        std::shared_ptr<WebSocket> websocket_ptr = std::make_shared<WebSocket>(request, response);
        websocket_ptr->setReceiveTimeout(Poco::Timespan(10, 0, 0, 0, 0));
        app.logger().information("WebSocket connection established.");
        unsigned char buffer[4096];
        int flags, bytes_received;
        do {
            bytes_received = websocket_ptr->receiveFrame(buffer, sizeof (buffer), flags);
            if ((flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE) {
                WebSocketMessage in_msg(buffer, flags, bytes_received);
                ws_server->receive_message(websocket_ptr, in_msg);
            } else {
                std::cout << "Client requested to close the connection" << std::endl;
            }
        } while (((flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE) && bytes_received > 0);

        app.logger().information("WebSocket connection closed.");
    } catch (WebSocketException& exc) {
        app.logger().log(exc);
        switch (exc.code()) {
            case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
                response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
                // fallthrough
            case WebSocket::WS_ERR_NO_HANDSHAKE:
            case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
            case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
                response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
                response.setContentLength(0);
                response.send();
                break;
        }
    }
    app.logger().information("WebSocket connection terminated.");
}