/* 
 * File:   TimeRequestHandler.h
 * Author: huuhoa
 *
 * Created on October 27, 2015, 11:39 AM
 */

#ifndef TIMEREQUESTHANDLER_H
#define	TIMEREQUESTHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>


class TimeRequestHandler: public Poco::Net::HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
    TimeRequestHandler(const std::string& format): 
        _format(format)
    {
    }
        
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
    std::string _format;
};

#endif	/* TIMEREQUESTHANDLER_H */

