/* 
 * File:   RequestHandlerFactory.h
 * Author: tamvh
 *
 * Created on December 28, 2015, 4:39 PM
 */

#ifndef REQUESTHANDLERFACTORY_H
#define REQUESTHANDLERFACTORY_H

#include <iostream>
#include <stdio.h>

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/Application.h>
#include "zapiws/ZApiWS.h"

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    RequestHandlerFactory();
    RequestHandlerFactory(std::shared_ptr<ZApiWS> test_srv);
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
private:
    std::shared_ptr<ZApiWS> ws_server;
};

#endif /* REQUESTHANDLERFACTORY_H */

