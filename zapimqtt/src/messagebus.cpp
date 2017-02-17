#include "messagebus.h"
#include "message.h"
#include "mqttbus.h"

#include <Poco/Delegate.h>
#include <Poco/Timestamp.h>
#include <Poco/Util/Application.h>
#include <Poco/Logger.h>
#include <iostream>

namespace iot {
namespace messagebus {

using namespace MQTT;

MessageBus::MessageBus() :
    _shardId(0),
    _sequenceId(0)
{

}

MessageBus::~MessageBus()
{
    if (_mqttClient) {
        _mqttClient->messageArrived -= Poco::delegate(this, &MessageBus::event__messageArrived);
    }
}

void MessageBus::initialize(Poco::Util::AbstractConfiguration &config)
{
    if (_mqttClient) {
        return;
    }

    std::string baseConfig = "iot.messagebus";

    _mqttClient = MQTTClient::createClient(config, baseConfig);
    if (!_mqttClient) {
        Poco::Util::Application& app = Poco::Util::Application::instance();
        app.logger().error("Cannot find configuration for %0s", baseConfig);
    }
    _mqttClient->messageArrived += Poco::delegate(this, &MessageBus::event__messageArrived);

    _shardId = config.getInt(baseConfig + ".shardId", 0);
}

int32_t MessageBus::subscribe(const Channel &channel)
{
    if (_mqttClient) {
        _mqttClient->subscribe(channel.toString(), 0);
    }
    return 0;
}

int32_t MessageBus::sendMessage(Poco::SharedPtr<Message> message, const Channel &channel)
{
    return _mqttClient->publish(channel.toString(), message->toPayload(), 0);
}

void MessageBus::event__messageArrived(const void* pSender,
                                       const iot::messagebus::MQTT::MQTTMessageArrivedEvent& data)
{
    (void)pSender;
    if (data.message.payload.empty()) {
        return;
    }

    try
    {
        Message::Ptr msg = new Message();
        if (!msg->fromPayload(data.message.payload)) {
            std::cerr << "Unknown message format" << std::endl;
            return;
        }

        MessageArrivedEvent event;
        event.handled = true;
        event.message = msg;
        event.topic = data.topic;
        event.dup = data.dup;

        try {
            messageArrived(this, event);
        } catch (Poco::Exception &eventEx) {
            puts("Error while handling message");
            puts(eventEx.displayText().c_str());
        }
    }
    catch (Poco::Exception &ex)
    {
        std::cerr << "Exception while processing message: " << ex.displayText() << std::endl;
    }
}

// follows article: http://instagram-engineering.tumblr.com/post/10853187575/sharding-ids-at-instagram
// Each of our IDs consists of:
//
// 41 bits for time in milliseconds (gives us 41 years of IDs with a custom epoch)
// 13 bits that represent the logical shard ID
// 10 bits that represent an auto-incrementing sequence, modulus 1024.
// This means we can generate 1024 IDs, per shard, per millisecond
//
// Let's say, our ‘epoch’ begins on January 1st, 2015.
// Timestamp in milliseconds: 1420070400000
uint64_t MessageBus::newToken()
{
    Poco::Timestamp currentTime;
    Poco::Timestamp::TimeVal mEpochSince1970 = currentTime.epochMicroseconds();
    uint64_t token;
    // we fill the left-most 41 bits with this value with a left-shift:
    token = (mEpochSince1970 - 1420070400000) << (64-41);

    // Next, we take the shard ID for this particular piece of data we’re trying to insert.
    // Let’s say we’re sharding by user ID, and there are 2048 logical shards;
    // if our user ID is 31341, then the shard ID is 31341 % 2048 -> 1341.
    // We fill the next 13 bits with this value:
    token |= (_shardId % 2048) << (64-41-13);

    // Finally, we take whatever the next value of our auto-increment sequence
    // (this sequence is unique to each running session) and fill out the remaining bits.
    // which we take and mod by 1024 (so it fits in 10 bits) and include it too:

    token |= (_sequenceId % 1024);
    _sequenceId ++;
    return token;
}

} } // namespace iot::messagebus

