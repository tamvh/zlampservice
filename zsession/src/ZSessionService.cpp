/*
 * File:   ZSessionService.cpp
 * Author: huuhoa
 *
 * Created on November 3, 2015, 4:55 PM
 */

#include <memory>
#include <sstream>
#include <string>

#include <Poco/Timestamp.h>
#include <Poco/Util/Application.h>

#include <zsession/ZSessionService.h>
#include <zcommon/ZServiceLocator.h>
#include "sessiondata.h"


namespace {

const std::string aesPassword = "12345678901234567890123456789012";
const std::string aesSalt = "salty";

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
uint64_t generateId()
{
    Poco::Timestamp currentTime;
    Poco::Timestamp::TimeVal mEpochSince1970 = currentTime.epochMicroseconds();
    int16_t _shardId = 1001;
    static int16_t _sequenceId = 0;
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
}

ZSessionService::ZSessionService() {
}

ZSessionService::~ZSessionService() {
}

/// Validate existing authentication token
/// @return ZErrorCode::Authentication_*
ZErrorCode ZSessionService::validate(const std::string& token, int32_t& userId) const {
//    SessionData session_parser(aesPassword, aesSalt, token);
//
//    if (session_parser.state() != ZErrorCode::OK) {
//        return session_parser.state();
//    }
//
//    uint64_t sessionId = session_parser.sessionId();
//    userId = session_parser.userId();
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    std::stringstream key;
//    key << "users:" << userId << ":sessions";
//    if (!dbProxy->SISMEMBER(key.str(), std::to_string(sessionId))) {
//        // authentication token is valid, however is deleted by other means
//        Poco::Util::Application::instance().logger().warning("session is not registered");
//        return ZErrorCode::Authentication_TokenExpired;
//    }

    return ZErrorCode::OK;
}

ZErrorCode ZSessionService::validate_jwt(const std::string& jwt, int32_t& userId) const {
//    SessionData session_parser(aesPassword, aesSalt, std::string());
//
//    if (session_parser.decode_jwt(jwt) != ZErrorCode::OK) {
//        return session_parser.state();
//    }
//
//    uint64_t sessionId = session_parser.sessionId();
//    userId = session_parser.userId();
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    std::stringstream key;
//    key << "users:" << userId << ":sessions";
//    if (!dbProxy->SISMEMBER(key.str(), std::to_string(sessionId))) {
//        // authentication token is valid, however is deleted by other means
//        Poco::Util::Application::instance().logger().warning("session is not registered. key [%s], sessionId [%s]",
//            key.str(), std::to_string(sessionId));
//        return ZErrorCode::Authentication_TokenExpired;
//    }

    return ZErrorCode::OK;
}

/// Create new authentication token for given userId
/// @param token holds authentication token when success
/// @return ZErrorCode::Authentication_*
ZErrorCode ZSessionService::create(int32_t userId, std::string& token) {
//    SessionData session_creator(aesPassword, aesSalt, userId);
//    uint64_t sessionId = generateId();
//    token = session_creator.encode(sessionId);
//
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    std::stringstream key;
//    key << "users:" << userId << ":sessions";
//    if (!dbProxy->SADD(key.str(), { std::to_string(sessionId) })) {
//        // authentication token is valid, however is deleted by other means
//        Poco::Util::Application::instance().logger().warning("Failed to generate session");
//        return ZErrorCode::Authentication_FailedToGenerateToken;
//    }

    return ZErrorCode::OK;
}

ZErrorCode ZSessionService::create_jwt(int32_t userId, const std::string& claims, std::string& token) {
//    SessionData session_creator(aesPassword, aesSalt, userId);
//    uint64_t sessionId = generateId();
//    token = session_creator.encode_jwt(sessionId, claims);
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    std::stringstream key;
//    key << "users:" << userId << ":sessions";
//    if (!dbProxy->SADD(key.str(), { std::to_string(sessionId) })) {
//        // authentication token is valid, however is deleted by other means
//        Poco::Util::Application::instance().logger().warning("Failed to generate session");
//        return ZErrorCode::Authentication_FailedToGenerateToken;
//    }

    return ZErrorCode::OK;
}

