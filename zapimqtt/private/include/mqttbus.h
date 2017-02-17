//
// MQTTClient.h
//
// $Id$
//
// Library: messagebus/MQTT
// Package: MQTTClient
// Module:  MQTTClient
//
// Definition of the MQTTClient interface.
//
// Copyright (c) 2015, VNG.
// All rights reserved.
//

#ifndef SYSTEM_MESSAGEBUS_MQTT_MQTTClient_INCLUDED
#define SYSTEM_MESSAGEBUS_MQTT_MQTTClient_INCLUDED


#include "Poco/Poco.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Util/AbstractConfiguration.h"
#include <vector>


namespace iot {
namespace messagebus {
namespace MQTT {


//@ serialize
struct MQTTMessage
    /// This structure encapsulates a MQTT message.
{
    MQTTMessage(int q = 0):
        qos(q),
        retained(false)
    {
    }

    MQTTMessage(const std::string& p, int q):
        payload(p),
        qos(q),
        retained(false)
    {
    }

    std::string payload;
        /// The payload of the MQTT message.

    int qos;
        /// The quality of service (QoS) assigned to the message.
        /// There are three levels of QoS:
        ///   * 0: Fire and forget - the message may not be delivered.
        ///   * 1: At least once - the message will be delivered, but may be
        ///        delivered more than once in some circumstances.
        ///   * 2: Once and one only - the message will be delivered exactly once.

    //@ mandatory=false
    bool retained;
        /// The retained flag serves two purposes depending on whether the message
        /// it is associated with is being published or received.
        ///
        ///   * retained = true: For messages being published, a true setting
        ///     indicates that the MQTT server should retain a copy of the message.
        ///     The message will then be transmitted to new subscribers to a topic
        ///     that matches the message topic. For subscribers registering a new
        ///     subscription, the flag being true indicates that the received message
        ///     is not a new one, but one that has been retained by the MQTT server.
        ///
        ///   * retained = false: For publishers, this ndicates that this message
        ///     should not be retained by the MQTT server. For subscribers, a false
        ///     setting indicates this is a normal message, received as a result of it
        ///     being published to the server.
};


//@ serialize
struct MQTTMessageArrivedEvent
    /// Event arguments for MQTTClient::messageArrived.
{
    std::string topic;
        /// The topic the message has been published to.

    MQTTMessage message;
        /// The published message.

    bool dup;
        /// The dup flag indicates whether or not this message is a duplicate.
        /// It is only meaningful when receiving QoS1 messages.
        /// When true, the client application should take appropriate action to
        /// deal with the duplicate message.

    bool handled;
        /// The handled flag must be set by the event delegate after processing
        /// of the message to indicate whether the message has been successfully
        /// processed. If set to false, the MQTT client will attempt to deliver
        /// the message again. The handled flag defaults to true. If the event delegate
        /// throws, the handled flag will be set to false by the framework. This
        /// means that in most cases the delegate does not need to concern itself with
        /// this flag.
};


//@ serialize
struct MQTTMessageDeliveredEvent
    /// Event arguments for MQTTClient::messageDelivered.
{
    int token;
        /// The delivery token.
};


//@ serialize
struct ConnectionLostEvent
    /// Event arguments for MQTTClient::connectionLost.
{
    std::string cause;
};


//@ serialize
struct TopicQoS
    /// A vector of these is given to MQTTClient::subscribeMany.
{
    TopicQoS():
        qos(0)
    {
    }

    TopicQoS(const std::string& t, int q = 0):
        topic(t),
        qos(q)
    {
    }

    std::string topic;
        /// The topic name, which may contain wildcards.

    int qos;
        /// The QoS level (0, 1 or 2).
};

//@ remote
class MQTTClient
    /// The interface for MQTT clients.
    ///
    /// Implementations are expected to receive their client ID and
    /// server URI via an implementation defined configuration mechanism.
    /// Once configured, a MQTTClient always uses the same client ID and
    /// connects to the same server. A MQTT client should automatically
    /// attempt to reconnect if the connection to the server is lost.
{
public:
    typedef Poco::SharedPtr<MQTTClient> Ptr;

    static Ptr createClient(Poco::Util::AbstractConfiguration &config, std::string &configPrefix);
public:
    Poco::BasicEvent<const MQTTMessageArrivedEvent> messageArrived;
        /// Fired when a message has been received for one of
        /// the subscribed topics.

    Poco::BasicEvent<const MQTTMessageDeliveredEvent> messageDelivered;
        /// Fired when a message has been delivered.

    Poco::BasicEvent<const ConnectionLostEvent> connectionLost;
        /// Fired when the connection to the MQTT server has been lost.

    MQTTClient();
        /// Creates the MQTTClient.

    virtual ~MQTTClient();
        /// Destroys the MQTTClient.

    virtual void connect() = 0;
        /// Connects to the MQTT server, if not yet connected.
        ///
        /// Throws a Poco::IOException if the connection cannot be established.

    virtual void disconnect(int timeout) = 0;
        /// This function attempts to disconnect the client from the MQTT server.
        /// In order to allow the client time to complete handling of messages that are
        /// in-flight when this function is called, a timeout period is specified.
        /// When the timeout period has expired, the client disconnects even if there
        /// are still outstanding message acknowledgements. The next time the client
        /// connects to the same server, any QoS 1 or 2 messages which have not completed
        /// will be retried depending on the clean session settings for both the previous
        /// and the new connection.

    virtual const std::string& id() const = 0;
        /// Returns the configured client ID.

    virtual const std::string& serverURI() const = 0;
        /// Returns the configured server URI.

    virtual bool connected() const = 0;
        /// Returns true if the client is currently connected to the server.

    virtual std::vector<TopicQoS> subscribedTopics() const = 0;
        /// Returns a vector containing all currently subscribed
        /// topics with their QoS level.

    virtual int publish(const std::string& topic, const std::string& payload, int qos) = 0;
        /// Publishes the given message on the given topic, using the given QoS.
        ///
        /// Returns a delivery token which can be used with the messageDelivered
        /// event to verify that the message has been delivered.
        ///
        /// Throws a Poco::IOException if the message cannot be published.

    virtual int publishMessage(const std::string& topic, const MQTTMessage& message) = 0;
        /// Publishes the given message on the given topic.
        ///
        /// Returns a delivery token which can be used with the messageDelivered
        /// event to verify that the message has been delivered.
        ///
        /// Throws a Poco::IOException if the message cannot be published.

    virtual void subscribe(const std::string& topic, int qos) = 0;
        /// This function attempts to subscribe the client to a single topic,
        /// which may contain wildcards. This call also specifies the Quality of service
        /// requested for the subscription.
        ///
        /// Throws a Poco::IOException if there was a problem registering the
        /// subscription.

    virtual void unsubscribe(const std::string& topic) = 0;
        /// This function attempts to remove an existing subscription made by the client.
        ///
        /// Throws a Poco::IOException if there was a problem removing the
        /// subscription.

    virtual void subscribeMany(const std::vector<TopicQoS>& topicsAndQoS) = 0;
        /// This function attempts to subscribe the client to a list of topics (with
        /// associated QoS levels), which may contain wildcards.
        ///
        /// Throws a Poco::IOException if there was a problem registering the
        /// subscriptions.

    virtual void unsubscribeMany(const std::vector<std::string>& topics) = 0;
        /// This function attempts to remove existing subscriptions to a list of
        /// topics made by the specified client.
        ///
        /// Throws a Poco::IOException if there was a problem removing the
        /// subscriptions.
};


} } } // namespace iot::messagebus::MQTT


#endif // SYSTEM_MESSAGEBUS_MQTT_MQTTClient_INCLUDED
