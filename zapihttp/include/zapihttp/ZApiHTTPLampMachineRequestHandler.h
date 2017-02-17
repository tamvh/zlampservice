/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZApiHTTPCoffeeMachineRequestHandler.h
 * Author: tamvh
 *
 * Created on April 13, 2016, 10:26 AM
 */
#ifndef ZAPIHTTPCOFFEEMACHINEREQUESTHANDLER_H
#define ZAPIHTTPCOFFEEMACHINEREQUESTHANDLER_H
#include <memory>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>

#include <zcommon/ErrorCode.h>
#include <zapihttp/ZApiHTTP.h>
#include <zapihttp/ZApiHTTPRequestBaseHandler.h>



class ZApiHTTPLampMachineRequestHandler : public ZApiHTTPRequestBaseHandler {
public:
    ZApiHTTPLampMachineRequestHandler(const std::string& path, std::shared_ptr<ZApiHTTP> ws_server);
    virtual ~ZApiHTTPLampMachineRequestHandler();
public:
    static bool CanHandleRequest(const std::string& path, const std::string& method);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
protected:
    void handleChangeStatus(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    void handleGetStatus(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    void fillterSTT(const std::string &sttLamp1, const std::string &sttLamp2, Poco::JSON::Object::Ptr & responseData);
private:
    std::shared_ptr<ZApiHTTP> _ws_server;
};

#endif /* ZAPIHTTPCOFFEEMACHINEREQUESTHANDLER_H */

