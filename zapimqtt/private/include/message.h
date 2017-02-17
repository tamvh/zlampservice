#ifndef IOTSYSTEM_MESSAGE_H
#define IOTSYSTEM_MESSAGE_H

#include <string>
#include <Poco/SharedPtr.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/DynamicStruct.h>

namespace iot {
namespace messagebus {

typedef std::string MessagePayload;

class MessageData
{
public:
    typedef Poco::SharedPtr<MessageData> Ptr;
    static Ptr null_message;
public:
    virtual ~MessageData();

    //! Derived class will populate @data member
    virtual Poco::Dynamic::Var toJSON() const = 0;

    //! Derived class will extract properties from @data member
    virtual bool fromJSON(const Poco::Dynamic::Var &data) = 0;

public:
    template<typename T, typename U = T>
    bool tryGet(const Poco::DynamicStruct& ds, const std::string &varName, U& value) {
        if (ds[varName].isEmpty()) {
            return false;
        }

        value = static_cast<U>(ds[varName].convert<T>());
        return true;
    }
};

class Message
{
public:
    typedef Poco::SharedPtr<Message> Ptr;
    typedef enum {
        UnknownType,
        RequestType,
        ResponseType
    } MessageType;

    static Ptr null_message;
public:
    Message();
    virtual ~Message();
    MessagePayload toPayload() const;
    bool fromPayload(const MessagePayload &payload);
public:
    std::string command() const { return _command; }
    uint64_t token() const { return _token; }
    MessageType type() const { return _type; }
    MessageData::Ptr data() const { return _data; }
    int32_t errorCode() const { return _errorCode; }
    std::string errorMessage() const { return _errorMessage; }
public:
    void setCommand(const std::string &value);
    void setToken(const uint64_t value);
    void setType(const MessageType value);
    void setData(MessageData::Ptr data);
    void setErrorCode(const int32_t value);
    void setErrorMessage(const std::string &value);
private:
    std::string _command;    // @cmd
    uint64_t _token;         // @token
    MessageType _type;       // @type: currently hold two values: Request, Response
    MessageData::Ptr _data;  // @data: hold message detail
    int32_t _errorCode;      // @error_code hold non-zero value when error occurs
    std::string _errorMessage;//@error_message present when there is an extra message
                             // to describe more about the error
};

MessageData::Ptr messageFromData(const std::string &command,
                                 const Message::MessageType type,
                                 const Poco::Dynamic::Var &data);

} } // namespace iot::messagebus

#endif // IOTSYSTEM_MESSAGE_H
