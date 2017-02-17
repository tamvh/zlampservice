/*
 * File:   ZUserManager.cpp
 * Author: huuhoa
 *
 * Created on October 23, 2015, 2:05 PM
 */
#include <sstream>
#include <algorithm>
#include <string>

#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/NumberParser.h>

#include <zcommon/ZServiceLocator.h>
#include <zcommon/ZDBKey.h>
#include <zdevicemanager/ZLog.h>

#include "zdevicemanager/ZDeviceManager.h"

ZCoffeeManager::ZCoffeeManager() {
}

ZCoffeeManager::~ZCoffeeManager() {
}

bool ZCoffeeManager::initialize() {
    return true;
}

bool ZCoffeeManager::start() {
    return true;
}

bool ZCoffeeManager::stop() {
    return true;
}

bool ZCoffeeManager::cleanup() {
    return true;
}

int32_t ZCoffeeManager::create(const std::string& userName, const int16_t& type) {
    
    
    
    
    
//    ZUserInfo userInfo;
//    userInfo.setUserName(userName);
//    userInfo.setPassword(password);
//    userInfo.setDisplayName(displayName);
//    userInfo.setAvatar(avatar);
//    userInfo.setCreatedAt(time(NULL));
//    userInfo.setUpdatedAt(time(NULL));
//
//    ZIdGenerator* generator = ZServiceLocator::instance()->get<ZIdGenerator>(ZServiceLocator::ServiceId::IDGenerator);
//    int32_t userId = generator->getNext(ZDBKey::generatorUsers());
//    userInfo.setUserId(userId);
//    std::string key = ZDBKey::UserEntry(userId);
//
//    saveToDB(userInfo);
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//
//    // create apikey for new user
//    std::string uuid_str = generator->createUuid();
//    dbProxy->HSET(key, ZDBKey::apiKey(), uuid_str);
//    dbProxy->HSET(ZDBKey::UserApiKey(), uuid_str, key);
//    dbProxy->HSET(ZDBKey::UserEmail(), userName, std::to_string(userId));
//    dbProxy->SADD(ZDBKey::UserSet(),{key});
//    return userId;
}

void ZCoffeeManager::saveToDB(ZLog& userInfo) {
//    std::string key = ZDBKey::UserEntry(userInfo.userId());
//
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    dbProxy->HMSET(key,{
//        { "userId", std::to_string(userInfo.userId())},
//        { "userName", userInfo.userName()},
//        { "displayName", userInfo.displayName()},
//        { "avatar", userInfo.avatar()},
//        { "password", userInfo.password()},
//        { "createdAt", std::to_string(userInfo.createdAt())},
//        { "updatedAt", std::to_string(userInfo.updatedAt())},
//    });
}

/// Lấy thông tin về một tài khoản có sẵn

ZLog::Ptr ZCoffeeManager::get(int32_t userId) {
//    std::string userkey = ZDBKey::UserEntry(userId);
//
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    if (dbProxy->HLEN(userkey) == 0) {
//        ZUserInfo::Ptr empty;
//        return empty;
//    }
//
//    ZUserInfo::Ptr user(new ZUserInfo);
//
//    ZDBProxy::StringList vals = dbProxy->HMGET(userkey, {
//        "userId", "userName", "displayName", "avatar", "password", "createdAt", "updatedAt"
//    });
//
//    Poco::Int64 i64Value;
//    Poco::Int32 i32Value;
//
//    if (Poco::NumberParser::tryParse(vals[0], i32Value)) {
//        user->setUserId(i32Value);
//    }
//    user->setUserName(vals[1]);
//    user->setDisplayName(vals[2]);
//    user->setAvatar(vals[3]);
//    user->setPassword(vals[4]);
//    if (Poco::NumberParser::tryParse64(vals[5], i64Value)) {
//        user->setCreatedAt(i64Value);
//    }
//
//    if (Poco::NumberParser::tryParse64(vals[6], i64Value)) {
//        user->setUpdatedAt(i64Value);
//    }
//
//    user->setApiKey(dbProxy->HGET(userkey, ZDBKey::apiKey()));
//    return user;
}

ZLog::Ptr ZCoffeeManager::getWithUserKey(const std::string& userkey) {
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    if (dbProxy->HLEN(userkey) == 0) {
//        ZUserInfo::Ptr empty;
//        return empty;
//    }
//
//    ZUserInfo::Ptr user(new ZUserInfo);
//
//    ZDBProxy::StringList vals = dbProxy->HMGET(userkey,{
//        "userId", "userName", "displayName", "avatar", "password", "createdAt", "updatedAt"
//    });
//
//    Poco::Int64 i64Value;
//    Poco::Int32 i32Value;
//
//    if (Poco::NumberParser::tryParse(vals[0], i32Value)) {
//        user->setUserId(i32Value);
//    }
//    user->setUserName(vals[1]);
//    user->setDisplayName(vals[2]);
//    user->setAvatar(vals[3]);
//    user->setPassword(vals[4]);
//    if (Poco::NumberParser::tryParse64(vals[5], i64Value)) {
//        user->setCreatedAt(i64Value);
//    }
//
//    if (Poco::NumberParser::tryParse64(vals[6], i64Value)) {
//        user->setUpdatedAt(i64Value);
//    }
//
//    user->setApiKey(dbProxy->HGET(userkey, ZDBKey::apiKey()));
//    return user;
}

ZLog::Ptr ZCoffeeManager::get(const std::string& userName) {
//    int32_t userId = -1;
//    ZUserInfo::Ptr user;
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    std::string userId_Str = dbProxy->HGET(ZDBKey::UserEmail(), userName);
//    if (userId_Str.empty()) {
//        return user;
//    }
//    if (!Poco::NumberParser::tryParse(userId_Str, userId)) {
//        return user;
//    }
//
//    return get(userId);
}

/// Lấy thông tin một số tài khoản theo danh sách khoá

ZLog::Map ZCoffeeManager::multiGet(const ZLog::KeyList& keyList) {
//    ZUserInfo::Map result;
//    for (int32_t userId : keyList) {
//        ZUserInfo::Ptr user = get(userId);
//        if (!user) {
//            continue;
//        }
//
//        result[userId] = user;
//    }
//
//    return result;
}

/// Lấy thông tin một số tài khoản theo danh sách tuần tự

ZLog::Map ZCoffeeManager::list(int32_t start, int32_t count) {
//    ZUserInfo::Map result;
//
//    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
//    ZDBProxy::StringList allkeys = dbProxy->SMEMBERS(ZDBKey::UserSet());
//
//    for (auto key : allkeys) {
//        ZUserInfo::Ptr user = getWithUserKey(key);
//        if (!user) {
//            continue;
//        }
//
//        result[user->userId()] = user;
//    }
//    return result;
}

/// Xoá tài khoản khỏi DB




