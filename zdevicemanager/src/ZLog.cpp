
//
// Created by Nguyễn Hữu Hoà on 10/23/15.
//

#include <sstream>
#include <zdevicemanager/ZLog.h>

ZLog::ZLog():
    _userName(""),
    _type(0),
    _createdAt(0)
{}

void ZLog::setUserName(const std::string& value) {
    this->_userName = value;
}

std::string ZLog::userName() const {
    return _userName;
}

void ZLog::setType(const int16_t value) {
    this->_type = value;
}

int16_t ZLog::type() const {
    return _type;
}

void ZLog::setCreatedAt(const int64_t value) {
    this->_createdAt = value;
}

int64_t ZLog::createdAt() const {
    return _createdAt;
}


