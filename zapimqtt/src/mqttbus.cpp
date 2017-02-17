//
// MQTTClient.cpp
//
// $Id$
//
// Library: system/messagebus/MQTT
// Package: MQTTClient
// Module:  MQTTClient
//
// Copyright (c) 2015, VNG.
// All rights reserved.
//

#include <Poco/StringTokenizer.h>
#include "mqttbus.h"
#include "mqttbusimpl.h"

namespace iot {
namespace messagebus {
namespace MQTT {


MQTTClient::MQTTClient()
{
}


MQTTClient::~MQTTClient()
{
}

MQTTClient::Ptr MQTTClient::createClient(Poco::Util::AbstractConfiguration &config, std::string &configPrefix)
{
    std::string serverURI = config.getString(configPrefix + ".serverURI", "");
    std::string clientId = config.getString(configPrefix + ".id", "");
    std::string persistencePath = config.getString(configPrefix + ".persistence.path", "");
    MQTTClientImpl::Persistence persistence = persistencePath.empty() ? MQTTClientImpl::MQTT_PERSISTENCE_NONE : MQTTClientImpl::MQTT_PERSISTENCE_FILE;

    if (!serverURI.empty())
    {
        MQTTClientImpl::ConnectOptions options;
        options.keepAliveInterval = config.getInt(configPrefix + ".keepAliveInterval", 60);
        options.retryInterval = config.getInt(configPrefix + ".retryInterval", 30);
        options.connectTimeout = config.getInt(configPrefix + ".connectTimeout", 20);
        options.cleanSession = config.getBool(configPrefix + ".cleanSession", true);
        options.reliable = config.getBool(configPrefix + ".reliable", false);
        options.username = config.getString(configPrefix + ".username", "");
        options.password = config.getString(configPrefix + ".password", "");
        options.willQoS = config.getInt(configPrefix + ".will.qos", 0);
        options.mqttVersion = config.getInt(configPrefix + ".mqttVersion", 0);
        Poco::StringTokenizer tok(config.getString(configPrefix + ".serverURIs", ""), ";,", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
        options.serverURIs.assign(tok.begin(), tok.end());

        options.willTopic = config.getString(configPrefix + ".will.topic", "");
        options.willMessage = config.getString(configPrefix + ".will.message", "");
        options.willRetained = config.getBool(configPrefix + ".will.retained", false);

        options.sslTrustStore = config.getString(configPrefix + ".ssl.trustStore", "");
        options.sslKeyStore = config.getString(configPrefix + ".ssl.keystore", "");
        options.sslPrivateKey = config.getString(configPrefix + ".ssl.privateKey", "");
        options.sslPrivateKeyPassword = config.getString(configPrefix + ".ssl.privateKeyPassword", "");
        options.sslEnabledCipherSuites = config.getString(configPrefix + ".ssl.enabledCipherSuites", "");
        options.sslEnableServerCertAuth = config.getBool(configPrefix + ".ssl.enableServerCertAuth", "");

        MQTTClientImpl::Ptr pMQTTClient = new MQTTClientImpl(serverURI, clientId, persistence, persistencePath, options);
        return pMQTTClient;
    } else {
        MQTTClientImpl::Ptr pMQTTClient;
        return pMQTTClient;
    }
}

} } } // namespace system::messagebus::MQTT
