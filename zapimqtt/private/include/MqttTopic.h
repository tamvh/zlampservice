/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MqttTopic.h
 * Author: tamvh
 *
 * Created on March 8, 2016, 12:43 PM
 */

#ifndef MQTTTOPIC_H
#define MQTTTOPIC_H
#include <string>

class MqttTopic {
public:
    MqttTopic();
public:
    static std::string requestTopic(const std::string& userApiKey, const std::string & deviceId, const std::string& apiName);
    static std::string responseTopic(const std::string& userApiKey, const std::string & deviceId, const std::string& apiName);
};

#endif /* MQTTTOPIC_H */

