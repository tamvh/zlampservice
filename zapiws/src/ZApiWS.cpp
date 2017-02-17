/*
 * File:   ZApiWS.cpp
 * Author: tamhuy
 *
 * Created on October 24, 2015, 3:19 PM
 */

#include <map>
#include <list>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/NetException.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Delegate.h>

#include <zcommon/ZServiceLocator.h>
#include <zworker/ZWorker.h>

#include "RequestHandlerFactory.h"
#include "ServerPacket.h"
#include "WebSocketMessage.h"
#include "ServerPacket.h"

#include "zapiws/ZApiWS.h"

using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::LayeredConfiguration;
using Poco::Util::Application;

class ZApiWS::Impl {
public:
    Poco::SharedPtr<HTTPServer> httpServer;
    Poco::SharedPtr<ServerSocket> serverSocket;

    typedef std::list<std::shared_ptr<Poco::Net::WebSocket>> WebSocketList;
    typedef std::map<std::string, WebSocketList> WebSocketMap;

    WebSocketMap list_client_ws;
};

ZApiWS::ZApiWS() : d_ptr(new Impl) {
}

ZApiWS::~ZApiWS() {
}

bool ZApiWS::initialize() {
    LayeredConfiguration& config = Application::instance().config();
    unsigned short port = (unsigned short) config.getInt("api.ws.port", 9981);
    int maxQueued = config.getInt("api.ws.maxQueued", 100);
    int maxThreads = config.getInt("api.ws.maxThreads", 16);
    ThreadPool::defaultPool().addCapacity(maxThreads);
    HTTPServerParams* pParams = new HTTPServerParams;
    pParams->setMaxQueued(maxQueued);
    pParams->setMaxThreads(maxThreads);
    // set-up a server socket
    d_ptr->serverSocket = new ServerSocket(port);
    // set-up a HTTPServer instance
    d_ptr->httpServer = new HTTPServer(new RequestHandlerFactory(std::shared_ptr<ZApiWS>(this)), *(d_ptr->serverSocket.get()), pParams);
    // start the HTTPServer

    // register event handlers
//    ZWorker* worker = ZServiceLocator::instance()->get<ZWorker>(ZServiceLocator::ServiceId::Worker);
//    worker->deviceDataUpdated += Poco::delegate(this, &ZApiWS::onDeviceDataUpdated);
//    worker->deviceDataCreated += Poco::delegate(this, &ZApiWS::onDeviceDataCreated);
//    worker->deviceDataDeleted += Poco::delegate(this, &ZApiWS::onDeviceDeletedDevice);
//    worker->deviceDataChangedInformation += Poco::delegate(this, &ZApiWS::onDeviceChangedDeviceInformation);

    return true;
}

bool ZApiWS::start() {
    d_ptr->httpServer->start();
    return true;
}

bool ZApiWS::stop() {
    d_ptr->httpServer->stop();

    return true;
}

bool ZApiWS::cleanup() {
    return true;
}

void ZApiWS::receive_message(std::shared_ptr<Poco::Net::WebSocket> websocket, const WebSocketMessage& msg) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    websocket_message_type msg_type = msg.get_message_type();
    std::string data;

    if (msg_type == websocket_message_type::WEB_SOCKET_UTF8_MESSAGE_TYPE) {
        Parser parser;
        Var result = parser.parse(msg.as_string());
        Object::Ptr json_val = result.extract<Object::Ptr>();
        ServerPacket packet(json_val);
        int32_t content_type = packet.get_content_type();

        if (content_type == packet_content_type::CLIENT_LOGIN) {
            this->handle_client_login(websocket, packet);
        } else if (content_type == packet_content_type::CLIENT_LOGOUT) {
            this->handle_client_logout(websocket, packet);
        } else if (content_type == packet_content_type::CHAT_TEXT_MSG) {
            //test
            data = packet.get_data();
            this->send_client_list(packet.get_local_client().getApikey(), data);
        }
    }
}

void ZApiWS::handle_client_login(std::shared_ptr<Poco::Net::WebSocket> websocket, const ServerPacket& clientData) {
    const ClientInfo& info = clientData.get_local_client();
    ZApiWS::Impl::WebSocketMap::iterator iLookup = d_ptr->list_client_ws.find(info.getApikey());
    if (iLookup == d_ptr->list_client_ws.end()) {
        ZApiWS::Impl::WebSocketList list;
        list.push_back(websocket);

        d_ptr->list_client_ws[info.getApikey()] = list;
    } else {
        iLookup->second.push_back(websocket);
    }
}

void ZApiWS::handle_client_logout(std::shared_ptr<Poco::Net::WebSocket> websocket, const ServerPacket& clientData) {
    const ClientInfo& info = clientData.get_local_client();
    ZApiWS::Impl::WebSocketMap::iterator iLookup = d_ptr->list_client_ws.find(info.getApikey());
    if (iLookup == d_ptr->list_client_ws.end()) {
        return;
    }

    iLookup->second.remove(websocket);
//    for (ZApiWS::Impl::WebSocketList::iterator iter = d_ptr->list_client_ws.begin(); iter != d_ptr->list_client_ws.end(); ++iter) {
//        if (*iter == websocket) {
//            d_ptr->list_client_ws.erase(iter);
//            break;
//        }
//    }
}

void ZApiWS::send_client_list(const std::string& apikey, const std::string& msg_out) {
    ZApiWS::Impl::WebSocketMap::iterator iLookup = d_ptr->list_client_ws.find(apikey);
    if (iLookup == d_ptr->list_client_ws.end()) {
        return;
    }

    for (std::shared_ptr<Poco::Net::WebSocket> ws_iter : iLookup->second) {
        ws_iter->sendFrame(msg_out.c_str(), msg_out.length(), WebSocket::FRAME_TEXT);
    }
}
