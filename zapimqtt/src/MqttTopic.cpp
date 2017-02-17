/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   MqttTopic.cpp
 * Author: tamvh
 *
 * Created on March 8, 2016, 12:43 PM
 */

#include "MqttTopic.h"

MqttTopic::MqttTopic() {
}

std::string MqttTopic::requestTopic(const std::string& userApiKey, const std::string & deviceId, const std::string& apiName) {
    return "/u/" + userApiKey + "/devices/" + deviceId + "/" + apiName + "/request";
}

std::string MqttTopic::responseTopic(const std::string& userApiKey, const std::string & deviceId, const std::string& apiName) {
    return "/u/" + userApiKey + "/devices/" + deviceId + "/" + apiName + "/response";
}
