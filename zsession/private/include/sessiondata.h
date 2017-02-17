#ifndef IOT_SESSION_SESSIONDATA_H
#define IOT_SESSION_SESSIONDATA_H

#include <stdint.h>
#include <string>
#include <zcommon/ErrorCode.h>

class SessionData
{
public:
    SessionData(const std::string &password, const std::string &salt, const std::string &session);
    SessionData(const std::string &password, const std::string &salt, int64_t userId, int64_t timestamp = -1);

    // encode current internal data and return session string
    std::string encode(int64_t sessionId) const;
    std::string encode_jwt(int64_t sessionId, const std::string& claims) const;
    ZErrorCode decode_jwt(const std::string& jwt);
public:
    int64_t userId() const { return _userId; }
    int64_t timestamp() const { return _timestamp; }
    int64_t sessionId() const { return _sessionId; }
    ZErrorCode state() const { return _state; }
    std::string errorMessage() const { return _errorMessage; }
private:
    // decode current session string into internal data
    void decode(const std::string &session);

private:
    std::string _password;
    std::string _salt;
    int64_t _userId;
    int64_t _timestamp;
    int64_t _sessionId;
    ZErrorCode _state;
    std::string _errorMessage;
    mutable std::string _sessionSeparator;
};

#endif // IOT_SESSION_SESSIONDATA_H
