/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebSocketMessage.h
 * Author: tamvh
 *
 * Created on January 11, 2016, 1:56 PM
 */

#ifndef WEBSOCKETMESSAGE_H
#define WEBSOCKETMESSAGE_H

#include <vector>
#include <memory>
#include <map>
#include <mutex>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Timespan.h"

enum websocket_message_type {
    WEB_SOCKET_BINARY_MESSAGE_TYPE,
    WEB_SOCKET_BINARY_FRAGMENT_TYPE,
    WEB_SOCKET_UTF8_MESSAGE_TYPE,
    WEB_SOCKET_UTF8_FRAGMENT_TYPE
};

class WebSocketMessage {
public:
    WebSocketMessage(unsigned char* buffer, int flags, int n);
    WebSocketMessage(const std::string& msg);

    int get_flags() const;
    const std::vector<unsigned char>& get_data() const;
    websocket_message_type get_message_type() const;

    const std::string as_string() const;
private:
    std::vector<unsigned char> m_data;
    websocket_message_type m_msg_type;
};

#endif /* WEBSOCKETMESSAGE_H */

