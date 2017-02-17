/*
 * File:   VersionRequestHandler.cpp
 * Author: huuhoa
 *
 * Created on December 04, 2015, 11:39 AM
 */

#include <zcommon/version.h>

#include "VersionRequestHandler.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

void VersionRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& ostr = response.send();
    ostr << "<html><head><title>ZCloud</title>";
    ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
//    ostr << gGIT_VERSION;
    ostr << "</p></body></html>";
}
