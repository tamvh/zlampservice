/*
 * File:   ZApiMQTT.cpp
 * Author: huuhoa
 *
 * Created on October 24, 2015, 3:17 PM
 */
#include <sstream>

#include <Poco/Util/Application.h>
#include <Poco/Util/LayeredConfiguration.h>
#include <Poco/RegularExpression.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>
#include <Poco/Delegate.h>

#include <zcommon/ZServiceInterface.h>
#include <zcommon/ZServiceLocator.h>
#include <zcommon/ZDBKey.h>
#include <zcommon/ErrorCode.h>
#include <zworker/ZWorker.h>
#include <zworker/ZDeviceEvent.h>

#include <zapimqtt/ZCloudReceiveMessageEvent.h>
#include "MqttClientWorker.h"
#include "MqttTopic.h"
#include "zapimqtt/ZApiMQTT.h"

#include "MQTTAsync.h"

using namespace std;
using Poco::Util::Application;
using Poco::Util::LayeredConfiguration;

class ZApiMQTT::Impl {
public:
    typedef std::map<int64_t, Poco::JSON::Object::Ptr> ObjectMap;
    ObjectMap list_object_request;
    Poco::SharedPtr<MqttClientWorker> mqttClientWorker;
};

ZApiMQTT::ZApiMQTT() : d_ptr(new Impl) {
}

ZApiMQTT::~ZApiMQTT() {
}

bool ZApiMQTT::initialize() {
    LayeredConfiguration& config = Application::instance().config();
    unsigned short port = (unsigned short) config.getInt("api.mqtt.port", 1883);
    std::string host = config.getString("api.mqtt.host", "localhost");
    std::string clientId = config.getString("api.mqtt.clientId", "");
    std::string topic = config.getString("api.mqtt.topic", "/u/#");

    d_ptr->mqttClientWorker = new MqttClientWorker(clientId, host, port);
    d_ptr->mqttClientWorker->preSubscribe(topic, 0);
    d_ptr->mqttClientWorker->autoReconnect(true);
    d_ptr->mqttClientWorker->beginConnect();
    d_ptr->mqttClientWorker->connect();

    ZWorker *worker = ZServiceLocator::instance()->get<ZWorker>(ZServiceLocator::ServiceId::Worker);

    worker->chooseCoffeeEvent += Poco::delegate(this, &ZApiMQTT::handlePublishMessage);
    d_ptr->mqttClientWorker->receiveMessageEvent += Poco::delegate(this, &ZApiMQTT::handleReceiveMessage);
    return true;
}

bool ZApiMQTT::start() {
    return true;
}

bool ZApiMQTT::stop() {
    return true;
}

bool ZApiMQTT::cleanup() {
    return true;
}

void ZApiMQTT::publishData(const std::string& topic, const std::string& msg) {
    if (!topic.empty() && !msg.empty()) {
        d_ptr->mqttClientWorker->publish(topic, msg);
    }
}

//Server -> Device

void ZApiMQTT::handlePublishMessage(const void *pSender, const ZDeviceEvent &event) {
    std::string topic = "coffee-machine/01";
    std::string msg = "";
    try {
        int32_t type = event.type();
        msg = to_string(type);
    } catch (Poco::Exception &ex) {
        Application& app = Application::instance();
        app.logger().error("Exception while processing message: %s", ex.displayText());
    }
    publishData(topic, msg);
}

//Device -> Server

void ZApiMQTT::handleReceiveMessage(const void *pSender, const ZCloudReceiveMessageEvent &event) {

}