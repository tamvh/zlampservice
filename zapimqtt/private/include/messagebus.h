#ifndef IOTSYSTEM_MESSAGEBUS_H
#define IOTSYSTEM_MESSAGEBUS_H

#include <stdint.h>
#include <vector>
#include <Poco/SharedPtr.h>
#include <Poco/BasicEvent.h>
#include <Poco/Util/AbstractConfiguration.h>

namespace iot {
namespace messagebus {

class Message;

namespace MQTT {
class MQTTClient;
struct MQTTMessageArrivedEvent;
}

/// Event arguments for MessageBus::messageArrived.
struct MessageArrivedEvent
{
    /// The topic the message has been published to.
    std::string topic;

    /// The published message.
    Poco::SharedPtr<Message> message;

    /// The dup flag indicates whether or not this message is a duplicate.
    /// It is only meaningful when receiving QoS1 messages.
    /// When true, the client application should take appropriate action to
    /// deal with the duplicate message.
    bool dup;

    /// The handled flag must be set by the event delegate after processing
    /// of the message to indicate whether the message has been successfully
    /// processed. If set to false, the MQTT client will attempt to deliver
    /// the message again. The handled flag defaults to true. If the event delegate
    /// throws, the handled flag will be set to false by the framework. This
    /// means that in most cases the delegate does not need to concern itself with
    /// this flag.
    bool handled;
};

class Channel
{
public:
    virtual std::string toString() const = 0;
};

class MQTTChannel : public Channel
{
public:
    MQTTChannel(const std::string &channel):
        _channel(channel)
    {

    }

    virtual std::string toString() const {
        return _channel;
    }
private:
    std::string _channel;
};

typedef Poco::SharedPtr<Channel> ChannelPtr;

class MessageBus
{
public:
    typedef Poco::SharedPtr<MessageBus> Ptr;
public:
    MessageBus();
    ~MessageBus();
public:
    /// Fired when a message has been received for one of
    /// the subscribed topics.
    Poco::BasicEvent<const MessageArrivedEvent> messageArrived;

public:
    void initialize(Poco::Util::AbstractConfiguration &config);

    void event__messageArrived(const void* pSender, const iot::messagebus::MQTT::MQTTMessageArrivedEvent& data);
public:
    int32_t sendMessage(Poco::SharedPtr<Message> message, const Channel &channel);
    int32_t subscribe(const Channel &channel);
    int32_t subscribe(const std::vector<Channel> &channels);
    uint64_t newToken();
private:
    Poco::SharedPtr<MQTT::MQTTClient> _mqttClient;
    int16_t _shardId;
    int16_t _sequenceId;
};

} }  // namespace system::messagebus

#endif // IOTSYSTEM_MESSAGEBUS_H
