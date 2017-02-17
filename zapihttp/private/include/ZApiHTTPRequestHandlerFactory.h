/*
 * File:   ZApiHTTPRequestHandlerFactory.h
 * Author: huuhoa
 *
 * Created on October 27, 2015, 11:35 AM
 */

#ifndef ZAPIHTTPREQUESTHANDLERFACTORY_H
#define	ZAPIHTTPREQUESTHANDLERFACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>

class ZApiHTTP;

class ZApiHTTPRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    ZApiHTTPRequestHandlerFactory(const std::string& format, const std::string& apiPrefix, std::shared_ptr<ZApiHTTP> api):
            _format(format),
            _apiPrefix(apiPrefix),
            _api(api)
    {
    }

public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
private:
    std::string _format;
    std::string _apiPrefix;
    std::shared_ptr<ZApiHTTP> _api;
};

#endif	/* ZAPIHTTPREQUESTHANDLERFACTORY_H */

