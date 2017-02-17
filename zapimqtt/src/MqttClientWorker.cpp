/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MqttClientWorker.cpp
 * Author: tamvh
 *
 * Created on March 7, 2016, 5:29 PM
 */
extern "C" {
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
}

#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <string.h>
#include <sys/param.h>
#include "zapimqtt/ZCloudReceiveMessageEvent.h"
#include "MqttClientWorker.h"

using namespace std;

MqttClientWorker::MqttClientWorker() {
}

MqttClientWorker::MqttClientWorker(
        const std::string& clientId,
        const std::string& hostBroker,
        int portBroker) : _clientId(clientId), _hostBroker(hostBroker), _portBroker(portBroker), _isConnected(false) {
    std::cout << "Creating mqtt client" << endl;
    std::string serverURI = "tcp://" + hostBroker + ":" + std::to_string(portBroker);
    MQTTClient_create(&_client, serverURI.c_str(), _clientId.c_str(),
            MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_setCallbacks(
            _client,
            this,
            &MqttClientWorker::mqttConnectionLost,
            &MqttClientWorker::mqttMessageArrived,
            &MqttClientWorker::mqttDelivered);
}

void MqttClientWorker::mqttDelivered(void *context, int dt) {
    MqttClientWorker *this_ = static_cast<MqttClientWorker*> (context);
    if (!this_) {
        return;
    }
    std::cout << "Message delivered:" << dt << endl;
}

int MqttClientWorker::mqttMessageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    MqttClientWorker *this_ = static_cast<MqttClientWorker*> (context);
    if (!this_) {
        return 0;
    }

    int i;
    char* payloadptr;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");

    payloadptr = (char*) message->payload;
    for (i = 0; i < message->payloadlen; i++) {
        putchar(*payloadptr++);
    }
    putchar('\n');
    std::string topic(topicName);
    std::string msg((char*) message->payload, message->payloadlen);
    this_->onMsg(topic, msg);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void MqttClientWorker::mqttConnectionLost(void *context, char *cause) {
    std::cout << "\nConnection lost\n";
    std::cout << "     cause: " << cause << std::endl;
}

bool MqttClientWorker::isConnected() {
    return MQTTClient_isConnected(_client);
}

void MqttClientWorker::onConnack(uint8_t retCode) {
    std::cout << "onConnack" << std::endl;
    if (!_topicList.empty() && !_qosList.empty()) {
        std::cout << "Subscribe to topic: " << _topicList.front() << std::endl;
        for (uint32_t i = 0; i < _topicList.size(); i++) {
            std::string topic = _topicList[i];
            int qos = _qosList[i];
            MQTTClient_subscribe(_client, topic.c_str(), qos);
        }
    }
}

void MqttClientWorker::onMsg(std::string& topic, std::string& msg) {
    cout << "Topic: " << topic << ": " << msg << endl;
    ZCloudReceiveMessageEvent event(msg, topic);
    receiveMessageEvent(this, event);
}

void MqttClientWorker::preSubscribe(std::string& topic, int qos) {
    if (isConnected()) {
        MQTTClient_subscribe(_client, topic.c_str(), qos);
    } else {
        _topicList.push_back(topic);
        _qosList.push_back(qos);
    }
}

void MqttClientWorker::connect() {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    conn_opts.keepAliveInterval = 30;
    conn_opts.cleansession = 1;
    rc = MQTTClient_connect(_client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }

    _isConnected = true;
    onConnack(0);
}



bool MqttClientWorker::publish(const std::string& topic, const std::string& message) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    pubmsg.payload = (void *) message.c_str();
    pubmsg.payloadlen = message.length();
    pubmsg.qos = 0;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(_client, topic.c_str(), &pubmsg, &token);
    return token;
}
