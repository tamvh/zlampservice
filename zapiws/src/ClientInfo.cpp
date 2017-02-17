/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientInfo.cpp
 * Author: tamvh
 * 
 * Created on January 11, 2016, 3:32 PM
 */

#include "ClientInfo.h"

ClientInfo::ClientInfo() {
}

ClientInfo::ClientInfo(const std::string & client_id, const std::string & client_name, const std::string & apikey)
: client_id_(client_id), client_name_(client_name), apikey_(apikey) {
}

ClientInfo::ClientInfo(const Poco::JSON::Object::Ptr & json_val) {
    client_id_ = json_val->optValue("client_id", std::string());
    client_name_ = json_val->optValue("screen_name", std::string());
}

ClientInfo::ClientInfo(const ClientInfo &src)
: client_id_(src.client_id_), client_name_(src.client_name_) {
}

void ClientInfo::setClient_id(const std::string & value) {
    this->client_id_ = value;
}

void ClientInfo::setClient_name(const std::string & value) {
    this->client_name_ = value;
}

void ClientInfo::setApikey(const std::string & value) {
    this->apikey_ = value;
}

void ClientInfo::addClient(const std::string & apikey) {
    list_client_.push_back(apikey);
}

std::vector<std::string> ClientInfo::getListClient() {
    return list_client_;
}

std::string ClientInfo::getClient_id() const {
    return client_id_;
}

std::string ClientInfo::getClient_name() const {
    return client_name_;
}

std::string ClientInfo::getApikey() const {
    return apikey_;
}

