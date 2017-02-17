/* 
 * File:   ServerApp.cpp
 * Author: huuhoa
 * 
 * Created on October 24, 2015, 3:00 PM
 */

#include <iostream>
#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/IntValidator.h>
#include <Poco/Util/HelpFormatter.h>


#include <zapihttp/ZApiHTTP.h>
#include <zapimqtt/ZApiMQTT.h>
#include <zapiws/ZApiWS.h>


#include <zcommon/ZServiceLocator.h>
#include <zcommon/ZMemProxy.h>
#include <zcommon/ZMemProxyLocal.h>
#include <zsession/ZSessionService.h>
#include <zworker/ZWorker.h>

#include "ServerApp.h"
class ServerApp::Impl {
public:

    Impl() :
    worker(new ZWorker()),
    memcachedProxy(new ZMemProxyLocal()),
    sessionService(new ZSessionService()) {
        ZServiceLocator::instance()->registerService(ZServiceLocator::ServiceId::MemCacheProxy, memcachedProxy.get());
        ZServiceLocator::instance()->registerService(ZServiceLocator::ServiceId::SessionService, sessionService.get());
        ZServiceLocator::instance()->registerService(ZServiceLocator::ServiceId::Worker, worker.get());

        services.push_back(new ZApiHTTP());
        services.push_back(new ZApiMQTT());
        services.push_back(new ZApiWS());

        services.push_back(worker);
    }
public:
    Poco::SharedPtr<ZWorker> worker;

    Poco::SharedPtr<ZMemProxy> memcachedProxy;
    Poco::SharedPtr<ZSessionService> sessionService;

    typedef Poco::SharedPtr<ZServiceInterface> ZServiceInterfacePtr;
    typedef std::vector<ZServiceInterfacePtr> ZServiceList;
    typedef std::vector<ZServiceInterfacePtr>::iterator ServiceIterator;
    typedef std::vector<ZServiceInterfacePtr>::reverse_iterator ServiceReverseIterator;

    std::vector<ZServiceInterfacePtr> services;    
};

ServerApp::ServerApp()
: _helpRequested(false) {
}

ServerApp::~ServerApp() {

}

void ServerApp::initialize(Application& self) {
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(self);
}

void ServerApp::uninitialize() {
    ServerApplication::uninitialize();
}

void ServerApp::defineOptions(Poco::Util::OptionSet& options) {
    ServerApplication::defineOptions(options);

    options.addOption(
            Poco::Util::Option("help", "h", "display help information on command line arguments")
            .required(false)
            .repeatable(false));

    options.addOption(
        Poco::Util::Option("port", "p", "Set http api listening port")
            .required(false)
            .argument("value")
            .validator(new Poco::Util::IntValidator(1000, 65535))
            .binding("api.http.port"));
}

void ServerApp::handleOption(const std::string& name, const std::string& value) {
    ServerApplication::handleOption(name, value);

    if (name == "help") {
        _helpRequested = true;
    }
}

void ServerApp::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A server application that serves the current date and time.");
    helpFormatter.format(std::cout);
}

int ServerApp::main(const std::vector<std::string>& args) {
    (void) args;
    if (_helpRequested) {
        displayHelp();
    } else {
        d_ptr = new Impl();

        
        for (Impl::ServiceIterator iter = d_ptr->services.begin();
                iter != d_ptr->services.end();
                iter++) {
            (*iter)->initialize();
        }

        for (Impl::ServiceIterator iter = d_ptr->services.begin();
                iter != d_ptr->services.end();
                iter++) {
            (*iter)->start();
        }

        // get parameters from configuration file
        //        _messageBus = new iot::messagebus::MessageBus();
        //        _messageBus->initialize(config());
        //
        //        _service = iot::service::ServiceFactory::createService();
        //        _service->setLogger(logger());
        //        _service->initialize(_messageBus);
        //        _service->start();
        // wait for CTRL-C or kill
        logger().information("Service is started");
        waitForTerminationRequest();

        // Stop the TCPServer
        //        _service->stop();
        for (Impl::ServiceReverseIterator riter = d_ptr->services.rbegin();
                riter != d_ptr->services.rend();
                riter++) {
            (*riter)->stop();
        }

        for (Impl::ServiceReverseIterator riter = d_ptr->services.rbegin();
                riter != d_ptr->services.rend();
                riter++) {
            (*riter)->cleanup();
        }
        logger().information("Service is stoped");
    }
    return Application::EXIT_OK;
}


