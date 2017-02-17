/* 
 * File:   ZMemProxy.cpp
 * Author: huuhoa
 * 
 * Created on October 23, 2015, 1:42 PM
 */

#include "zcommon/ZMemProxy.h"

ZMemProxy::ZMemProxy() {
}

ZMemProxy::~ZMemProxy() {
}

bool ZMemProxy::get(const std::string& collectionName, const std::string& key, std::string& value) {   
    return false;
}

bool ZMemProxy::add(const std::string& collectionName, const std::string& key, const std::string& value) {   
    return false;
}

bool ZMemProxy::remove(const std::string& collectionName, const std::string& key) {
    return false;
}

bool ZMemProxy::update(const std::string& collectionName, const std::string& key, const std::string& value) {
    return false;
}


