/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MqttClientWorker.h
 * Author: tamvh
 *
 * Created on March 7, 2016, 5:29 PM
 */

#ifndef MQTTCLIENTWORKER_H
#define MQTTCLIENTWORKER_H

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include <memory>
#include <Poco/BasicEvent.h>
extern "C" {
    #include "MQTTClient.h"
    #include "MQTTClientPersistence.h"
}
#include <zapimqtt/ZCloudReceiveMessageEvent.h>

class MqttClientWorker {
public:
    MqttClientWorker();
    MqttClientWorker(const std::string& clientId, const std::string& addr, int port);
    virtual ~MqttClientWorker() {}

public:
    virtual void onConnack(uint8_t retCode);
    void onMsg(std::string& topic, std::string& msg);

    void preSubscribe(std::string& topic, int qos);
    void autoReconnect(bool value) {}
    void beginConnect() {}
    void connect();

    bool isConnected();
    bool publish(const std::string& topic, const std::string& message);
    
    Poco::BasicEvent<const ZCloudReceiveMessageEvent> receiveMessageEvent;
protected:
    static void mqttDelivered(void *context, int dt);
    static int mqttMessageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
    static void mqttConnectionLost(void *context, char *cause);
private:

    std::string _clientId;
    std::string _hostBroker;
    int _portBroker;
    std::vector<std::string> _topicList;
    std::vector<uint8_t> _qosList;
    MQTTClient _client;
    bool _isConnected;
};

#endif /* MQTTCLIENTWORKER_H */

