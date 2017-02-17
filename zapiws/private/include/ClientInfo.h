/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ClientInfo.h
 * Author: tamvh
 *
 * Created on January 11, 2016, 3:32 PM
 */

#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <string>
#include <map>

#include <Poco/JSON/Object.h>

class ClientInfo {
public:
    ClientInfo();
    ClientInfo(const std::string & client_id, const std::string & client_name, const std::string & apikey);
    ClientInfo(const Poco::JSON::Object::Ptr & json_val);
    ClientInfo(const ClientInfo &src);
    void setClient_id(const std::string & value);
    void setClient_name(const std::string & value);
    void setApikey(const std::string & value);
    void addClient(const std::string & apikey);
    std::vector<std::string> getListClient();
    std::string getClient_id() const;
    std::string getClient_name() const;
    std::string getApikey() const;
private:
    std::string client_id_;
    std::string client_name_;
    std::string apikey_;
    std::vector<std::string> list_client_;
};

#endif /* CLIENTINFO_H */

