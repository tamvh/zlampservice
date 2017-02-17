#include "sessiondata.h"
#include <stdint.h>
#include <Poco/Timestamp.h>
#include <Poco/Timespan.h>
#include <Poco/NumberParser.h>
#include <Poco/NumberFormatter.h>
#include <Poco/String.h>
#include <Poco/Format.h>
#include <Poco/Logger.h>
#include "aes256.h"
#include "base64url.h"
#include <zcommon/ErrorCode.h>
#include <sstream>

SessionData::SessionData(const std::string &password, const std::string &salt, const std::string &session) :
    _password(password),
    _salt(salt),
    _userId(0),
    _timestamp(-1),
    _sessionId(0),
    _state(ZErrorCode::OK),
    _sessionSeparator(".")
{
    if (!session.empty()) {
        decode(session);
    }
}

SessionData::SessionData(const std::string &password, const std::string &salt, int64_t userId, int64_t timestamp) :
    _password(password),
    _salt(salt),
    _userId(userId),
    _timestamp(timestamp),
    _state(ZErrorCode::Authentication_InvalidToken),
    _sessionSeparator(".")
{
    if (_timestamp < 0) {
        Poco::Timestamp t;
        _timestamp = t.epochMicroseconds();
    }

    if (_userId <= 0) {
        _state = ZErrorCode::Authentication_InvalidToken;
    }
}

struct Session_Internal {
    uint64_t sessionId;
    uint64_t userId;
    uint64_t timestamp;
    uint64_t checksum;
};

struct Data32_Internal {
    uint8_t d1[16];
    uint8_t d2[16];
};

union Session {
    Session_Internal session;
    Data32_Internal data;
};

void SessionData::decode(const std::string &session_key)
{
    Poco::Logger& logger = Poco::Logger::get("Application");
    // session is encoded under following format
    // u.[uid].base64url/encrypted_data
    std::string session = Poco::trim(session_key);
    int32_t size = session.size();
    if (size < 3) {
        _state = ZErrorCode::Authentication_InvalidToken;
        logger.error("Session string is too short");
        _errorMessage = "Session string is too short";
        return;
    }

    if (session[0] != 'u') {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Session does not start with 'u'");
        return;
    }

    // extract number/uid
    Poco::UInt64 userId = 0;
    std::string encryptedData;
    std::string::size_type dotPos = session.find(_sessionSeparator);
    if (dotPos == std::string::npos) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Cannot get userId from session.");
        return;
    }
    std::string uidStr = session.substr(1, dotPos - 1);
    if (!Poco::NumberParser::tryParseUnsigned64(uidStr, userId)) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Cannot get userId from session. Id string: %[0]s", uidStr);
        return;
    }

    encryptedData = session.substr(dotPos + _sessionSeparator.length());

    if (userId == 0 || encryptedData.empty()) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("UserId == 0 or encrypted data in the session string is empty");
        return;
    }

    std::vector<uint8_t> data = base64url::decode(encryptedData);
    if (data.empty() || data.size() != sizeof(Session)) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Invalid data when decrypting session string. Data size: %[0]u. Encrypted string: %[1]s",
                     (unsigned int)data.size(),
                     encryptedData);
        return;
    }

    Session* session_data = reinterpret_cast<Session*>(&data[0]);
    // decrypts data
    aes256_context ctx;
    aes256_init(&ctx, (const uint8_t*)_password.c_str());
    aes256_decrypt_ecb(&ctx, session_data->data.d1);
    aes256_decrypt_ecb(&ctx, session_data->data.d2);
    aes256_done(&ctx);

    if (session_data->session.sessionId == 0) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Invalid sessionId");
        return;
    }

    if (session_data->session.userId != userId) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("UserId in the session string does not meet external userId");
        return;
    }

    uint64_t checksum = session_data->session.sessionId +
            session_data->session.userId +
            session_data->session.timestamp;
    if (checksum != session_data->session.checksum) {
        _state = ZErrorCode::Authentication_InvalidToken;
        _errorMessage = "Session is invalid";
        logger.error("Invalid checksum when validating session");
        return;
    }

    Poco::Timestamp timeCreated(session_data->session.timestamp);
    Poco::Timespan timespan(1, 0, 0, 0, 0);
    Poco::Timestamp currentTime;
    if (timeCreated + timespan < currentTime) {
        _state = ZErrorCode::Authentication_TokenExpired;
        _errorMessage = "Session is expired";
        logger.error("Session is expired");
        return;
    }

    _userId = session_data->session.userId;
    _timestamp = session_data->session.timestamp;
    _sessionId = session_data->session.sessionId;
    _state = ZErrorCode::OK;
    _errorMessage = "";
}

ZErrorCode SessionData::decode_jwt(const std::string &jwt_input)
{
    Poco::Logger& logger = Poco::Logger::get("Application");
    // session is encoded under following format
    // u.[uid].base64url/encrypted_data
    std::string jwt = Poco::trim(jwt_input);
    // extract data
    std::string::size_type firstDot = jwt.find_first_of('.');
    if (firstDot == std::string::npos) {
        _state = ZErrorCode::Authentication_InvalidToken;
        logger.error("Session string is too short");
        _errorMessage = "Session string is too short";
        return _state;
    }
    
    std::string::size_type secondDot = jwt.find('.', firstDot + 1);
    if (secondDot == std::string::npos) {
        _state = ZErrorCode::Authentication_InvalidToken;
        logger.error("Session string is too short");
        _errorMessage = "Session string is too short";
        return _state;
    }
    std::string session = jwt.substr(secondDot + 1);
    _sessionSeparator = "%24";
    decode(session);
    return _state;
}

std::string SessionData::encode(int64_t sessionId) const
{
    // session is encoded under following format
    // u.[uid].base64url/encrypted_data
    std::string session;

    Poco::Timestamp currentTime;
    Session session_data;
    session_data.session.userId = _userId;
    session_data.session.timestamp = currentTime.epochMicroseconds();
    session_data.session.sessionId = sessionId;
    session_data.session.checksum = session_data.session.sessionId +
            session_data.session.userId +
            session_data.session.timestamp;

    // encrypts data
    aes256_context ctx;
    aes256_init(&ctx, (const uint8_t*)_password.c_str());
    aes256_encrypt_ecb(&ctx, session_data.data.d1);
    aes256_encrypt_ecb(&ctx, session_data.data.d2);
    aes256_done(&ctx);

    // create base64url
    std::string encrypted = base64url::encode(session_data.data.d1, sizeof(Session));
    using Poco::format;
    format(session, "u%[1]Lu%[0]s%[2]s", _sessionSeparator, (Poco::UInt64)_userId, encrypted);

    return session;
}

std::string SessionData::encode_jwt(int64_t sessionId, const std::string& claims) const
{
    _sessionSeparator = "%24";
    // session is encoded under following format
    // u.[uid].base64url/encrypted_data
    std::string session = encode(sessionId);
    std::string bclaims = base64url::encode((const uint8_t*)claims.c_str(), claims.length());
    std::stringstream jwt;
    jwt << "jwt." << bclaims << "." << session;
    return jwt.str();
}

