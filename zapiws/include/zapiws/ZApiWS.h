/*
 * File:   ZApiWS.h
 * Author: huuhoa
 *
 * Created on October 24, 2015, 3:19 PM
 */

#ifndef ZAPIWS_H
#define ZAPIWS_H


#include <memory>
#include <iostream>
#include <stdio.h>

#include <Poco/Net/WebSocket.h>
#include <zcommon/ZServiceInterface.h>

class ZDeviceDataUpdatedEvent;
class ZDeviceDataDeletedEvent;
class ZDeviceDataCreatedEvent;
class ZDeviceDataChangeInformationEvent;
class WebSocketMessage;
class ServerPacket;

class ZApiWS : public ZServiceInterface {
public:
    ZApiWS();
    virtual ~ZApiWS();
public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();

    void receive_message(std::shared_ptr<Poco::Net::WebSocket> websocket, const WebSocketMessage& msg);
    void send_client_list(const std::string& apikey, const std::string& msg);
private:
    void handle_client_login(std::shared_ptr<Poco::Net::WebSocket> websocket, const ServerPacket& clientData);
    void handle_client_logout(std::shared_ptr<Poco::Net::WebSocket> websocket, const ServerPacket& clientData);

private:
    //! @section Event Handler
    //! Handle broadcast events

    //! Event broadcasted whenever data is updated for a device
    void onDeviceDataUpdated(const void *pSender, const ZDeviceDataUpdatedEvent &event);
    void onDeviceDataCreated(const void *pSender, const ZDeviceDataCreatedEvent &event);
    void onDeviceDeletedDevice(const void *pSender, const ZDeviceDataDeletedEvent &event);
    void onDeviceChangedDeviceInformation(const void *pSender, const ZDeviceDataChangeInformationEvent &event);
private:
    class Impl;

    std::shared_ptr<Impl> d_ptr;
};

#endif /* ZAPIWS_H */

