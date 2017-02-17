/*
 * File:   ZApiMQTT.h
 * Author: huuhoa
 *
 * Created on October 24, 2015, 3:17 PM
 */

#ifndef ZAPIMQTT_H
#define ZAPIMQTT_H

#include <vector>
#include <iostream>
#include <memory>
#include <Poco/JSON/Object.h>

class ZDeviceEvent;
class ZCloudReceiveMessageEvent;
class ZApiMQTT : public ZServiceInterface {
public:
    ZApiMQTT();
    virtual ~ZApiMQTT();

public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();
private:
    void publishData(const std::string& topic, const std::string& msg);
    void handlePublishMessage(const void *pSender, const ZDeviceEvent &event);
    void handleReceiveMessage(const void *pSender, const ZCloudReceiveMessageEvent &event);    
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif /* ZAPIMQTT_H */

