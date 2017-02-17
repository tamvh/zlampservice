/* 
 * File:   ServerApp.h
 * Author: huuhoa
 *
 * Created on October 24, 2015, 3:00 PM
 */

#ifndef SERVERAPP_H
#define	SERVERAPP_H

#include <Poco/Exception.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>

class ServerApp : public Poco::Util::ServerApplication {
public:
    ServerApp();
    ~ServerApp();
public:
    void initialize(Application& self);
    void uninitialize();
    void defineOptions(Poco::Util::OptionSet& options);
    void handleOption(const std::string& name, const std::string& value);
    void displayHelp();

    int main(const std::vector<std::string>& args);
private:
    bool _helpRequested;
    class Impl;
    Poco::SharedPtr<Impl> d_ptr;
};

#endif	/* SERVERAPP_H */

