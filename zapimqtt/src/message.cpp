#include "message.h"

#include <Poco/Dynamic/Struct.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <stdint.h>

using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::DynamicStruct;

namespace iot {
namespace messagebus {

MessageData::Ptr MessageData::null_message;
Message::Ptr Message::null_message;

std::string MessageTypeToString(Message::MessageType type) {
    switch (type) {
    case Message::RequestType:
        return "Request";
    case Message::ResponseType:
        return "Response";
    default:
        return "Unknown";
    }
}

Message::MessageType StringToMessageType(const std::string &type) {
    if (type == "Request") {
        return Message::RequestType;
    } else if (type == "Response") {
        return Message::ResponseType;
    } else {
        return Message::UnknownType;
    }
}

MessageData::~MessageData()
{

}

Message::Message() :
    _token(0),
    _type(Message::UnknownType),
    _errorCode(0)
{

}

Message::~Message()
{

}

void Message::setCommand(const std::string &value)
{
    _command = value;
}

void Message::setToken(const uint64_t value)
{
    _token = value;
}

void Message::setType(const MessageType value)
{
    _type = value;
}

void Message::setData(MessageData::Ptr data)
{
    _data = data;
}

void Message::setErrorCode(const int32_t value)
{
    _errorCode = value;
}

void Message::setErrorMessage(const std::string &value)
{
    _errorMessage = value;
}


MessagePayload Message::toPayload() const
{
    Poco::JSON::Object::Ptr root = new Poco::JSON::Object;
    root->set("cmd", _command);
    root->set("token", (Poco::UInt64)_token);
    root->set("type", MessageTypeToString(_type));
    if (_data) {
        root->set("data", _data->toJSON());
    }
    root->set("error_code", _errorCode);
    if (!_errorMessage.empty()) {
        root->set("error_message", _errorMessage);
    }

    std::stringstream oss;
    Poco::JSON::Stringifier::stringify(root, oss);
    return oss.str();
}

bool Message::fromPayload(const MessagePayload &payload)
{
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;

    if (payload.empty()) {
        return false;
    }

    Parser parser;
    try
    {
        Var result = parser.parse(payload);
        if (result.type() != typeid(Object::Ptr)) {
            return false;
        }

        Object::Ptr object = result.extract<Object::Ptr>();
        if (object->size() == 0) {
            return false;
        }

        Var cmdValue = object->get("cmd");
        if (cmdValue.isEmpty()) {
            return false;
        }
        _command = cmdValue.convert<std::string>();

        Var tokenValue = object->get("token");
        if (tokenValue.isEmpty()) {
            return false;
        }
        _token = tokenValue.convert<Poco::UInt64>();

        Var typeValue = object->get("type");
        if (typeValue.isEmpty()) {
            return false;
        }
        _type = StringToMessageType(typeValue.convert<std::string>());

        Var errorMessageValue = object->get("error_message");
        if (errorMessageValue.isEmpty()) {
            _errorMessage = "";
        } else {
            _errorMessage = errorMessageValue.convert<std::string>();
        }

        Var errorCodeValue = object->get("error_code");
        if (errorCodeValue.isEmpty()) {
            _errorCode = 0;
        } else {
            _errorCode = errorCodeValue.convert<Poco::Int32>();
        }

        Var data = object->get("data");
        if (data.isEmpty()) {
            _data = MessageData::null_message;
        } else {
            _data = messageFromData(_command, _type, data);
        }
        return true;
    }
    catch (Poco::Exception &ex)
    {
        std::cerr << "Exception while processing message: " << ex.displayText() << std::endl;
        return false;
    }

    return false;
}

} } // namespace iot::messagebus

