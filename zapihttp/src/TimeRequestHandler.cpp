/* 
 * File:   TimeRequestHandler.cpp
 * Author: huuhoa
 * 
 * Created on October 27, 2015, 11:39 AM
 */

#include "TimeRequestHandler.h"
#include <Poco/Util/Application.h>
#include <Poco/Timestamp.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

using Poco::Util::Application;

using Poco::Timestamp;
using Poco::DateTimeFormatter;

void TimeRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());

    Timestamp now;
    std::string dt(DateTimeFormatter::format(now, _format));

    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");

    std::ostream& ostr = response.send();
    ostr << "<html><head><title>HTTPTimeServer powered by POCO C++ Libraries</title>";
    ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
    ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
    ostr << dt;
    ostr << "</p></body></html>";
}
