/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerPacket.h
 * Author: tamvh
 *
 * Created on January 12, 2016, 1:49 PM
 */

#ifndef SERVERPACKET_H
#define SERVERPACKET_H

#include <vector>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>
#include "ClientInfo.h"

// Indicates of messages exchanged between client and server

typedef enum {
    NONE,
    CLIENT_LOGIN,
    CLIENT_LOGOUT,
    NEW_CONNECTED_CLIENTS,
    NEW_DISCONNECTED_CLIENTS,
    CHAT_TEXT_MSG

} packet_content_type;

class ServerPacket {
public:
    ServerPacket();
    ServerPacket(const Poco::JSON::Object::Ptr & json_val);
    Poco::Dynamic::Var as_json() const;
    void set_content_type(packet_content_type content_type);
    packet_content_type get_content_type();

    void add_to_client_list(const ClientInfo& client_info);
    const std::vector<ClientInfo>& get_client_list() const;

    void set_local_client(const ClientInfo& local_client);
    const ClientInfo& get_local_client() const;
    const std::string& get_data() const;
private:
    packet_content_type m_content_type;
    ClientInfo m_local_client;
    std::vector<ClientInfo> m_client_list;
    std::string data;
};

#endif /* SERVERPACKET_H */

