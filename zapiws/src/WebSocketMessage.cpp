/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebSocketMessage.cpp
 * Author: tamvh
 * 
 * Created on January 11, 2016, 1:56 PM
 */

#include "WebSocketMessage.h"

using namespace Poco::Net;

WebSocketMessage::WebSocketMessage(unsigned char* buffer, int flags, int n) : m_data(buffer, buffer + n) {
    switch (flags) {
        case WebSocket::FRAME_TEXT:
            m_msg_type = websocket_message_type::WEB_SOCKET_UTF8_MESSAGE_TYPE;
            break;
        case WebSocket::FRAME_BINARY:
            m_msg_type = websocket_message_type::WEB_SOCKET_BINARY_MESSAGE_TYPE;
            break;
    }
}

WebSocketMessage::WebSocketMessage(const std::string& msg) : m_data(msg.begin(), msg.end()) {
    m_msg_type = websocket_message_type::WEB_SOCKET_UTF8_MESSAGE_TYPE;
}

const std::vector<unsigned char>& WebSocketMessage::get_data() const {
    return m_data;
}

websocket_message_type WebSocketMessage::get_message_type()const {
    return m_msg_type;
}

int WebSocketMessage::get_flags() const {
    int flags = 0;

    switch (m_msg_type) {
        case websocket_message_type::WEB_SOCKET_UTF8_FRAGMENT_TYPE:
            flags = WebSocket::FRAME_OP_CONT | WebSocket::FRAME_OP_TEXT;
            break;
        case websocket_message_type::WEB_SOCKET_UTF8_MESSAGE_TYPE:
            flags = WebSocket::FRAME_FLAG_FIN | WebSocket::FRAME_OP_TEXT;
            break;
        case websocket_message_type::WEB_SOCKET_BINARY_FRAGMENT_TYPE:
            flags = WebSocket::FRAME_OP_CONT | WebSocket::FRAME_OP_BINARY;
            break;
        case websocket_message_type::WEB_SOCKET_BINARY_MESSAGE_TYPE:
            flags = WebSocket::FRAME_FLAG_FIN | WebSocket::FRAME_OP_BINARY;
            break;
    }

    return flags;
}

const std::string WebSocketMessage::as_string() const
{
	std::string temp(m_data.begin(), m_data.end());
	return temp;
}