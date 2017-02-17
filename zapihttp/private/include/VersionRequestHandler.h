/*
 * File:   VersionRequestHandler.h
 * Author: huuhoa
 *
 * Created on December 04, 2015, 11:39 AM
 */

#ifndef VERSIONREQUESTHANDLER_H
#define	VERSIONREQUESTHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


class VersionRequestHandler: public Poco::Net::HTTPRequestHandler
    /// Return a HTML document with the current build version.
{
public:
    VersionRequestHandler()
    {
    }

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

#endif	/* VERSIONREQUESTHANDLER_H */

