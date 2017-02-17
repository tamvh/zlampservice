/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerPacket.cpp
 * Author: tamvh
 * 
 * Created on January 12, 2016, 1:49 PM
 */

#include "ServerPacket.h"

ServerPacket::ServerPacket() {
    m_content_type = NONE;
}

ServerPacket::ServerPacket(const Poco::JSON::Object::Ptr & json_val) {
    m_content_type = static_cast<packet_content_type> (json_val->optValue("content_type", -1));
    m_local_client.setClient_id(json_val->optValue("client_id", std::string()));
    m_local_client.setClient_name(json_val->optValue("client_name", std::string()));
    m_local_client.setApikey(json_val->optValue("apikey", std::string()));
    data = json_val->optValue("data", std::string());
    m_client_list.push_back(m_local_client);
}

void ServerPacket::set_content_type(packet_content_type content_type) {
    m_content_type = content_type;
}

packet_content_type ServerPacket::get_content_type() {
    return m_content_type;
}

void ServerPacket::add_to_client_list(const ClientInfo& client_info) {
    m_client_list.push_back(client_info);
}

const std::vector<ClientInfo>& ServerPacket::get_client_list() const {
    return m_client_list;
}

void ServerPacket::set_local_client(const ClientInfo& local_client) {
    m_local_client = local_client;
}

const ClientInfo& ServerPacket::get_local_client() const {
    return m_local_client;
}

const std::string& ServerPacket::get_data() const {
    return data;
}

