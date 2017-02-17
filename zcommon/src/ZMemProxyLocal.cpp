/* 
 * File:   ZMemProxyLocal.cpp
 * Author: huuhoa
 * 
 * Created on October 23, 2015, 1:48 PM
 */

#include "zcommon/ZMemProxyLocal.h"

ZMemProxyLocal::ZMemProxyLocal() {
}

ZMemProxyLocal::~ZMemProxyLocal() {
}


bool ZMemProxyLocal::get(const std::string& collectionName, const std::string& key, std::string& value) {
    if (_database.find(collectionName) == _database.end()) {
        return false;
    }

    KeyValueCollection &collection = _database.at(collectionName);
    auto iter = collection.find(key);
    if (iter == collection.end()) {
        return false;
    }

    value = iter->second;
    return true;
}

bool ZMemProxyLocal::add(const std::string& collectionName, const std::string& key, const std::string& value) {
    auto kvIter = _database.find(collectionName);
    if (kvIter == _database.end()) {
        KeyValueCollection collection;
        collection[key] = value;
        _database[collectionName] = collection;
        return true;
    } else {
        KeyValueCollection& collection = kvIter->second;
        collection[key] = value;
        return true;
    }
}

bool ZMemProxyLocal::remove(const std::string& collectionName, const std::string& key) {
    auto kvIter = _database.find(collectionName);
    if (kvIter == _database.end()) {
        return false;
    }

    KeyValueCollection& collection = kvIter->second;
    collection.erase(key);
    if (collection.empty()) {
        _database.erase(collectionName);
    }
    return true;
}

bool ZMemProxyLocal::update(const std::string& collectionName, const std::string& key, const std::string& value) {
    auto kvIter = _database.find(collectionName);
    if (kvIter == _database.end()) {
        return false;
    }

    KeyValueCollection& collection = kvIter->second;
    auto cIter = collection.find(key);
    if (cIter == collection.end()) {
        return false;
    }
    collection[key] = value;
    return true;
}

