/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZCloudReceiveMessageEvent.h
 * Author: tamvh
 *
 * Created on March 22, 2016, 11:38 AM
 */

#ifndef ZCLOUDRECEIVEMESSAGEEVENT_H
#define ZCLOUDRECEIVEMESSAGEEVENT_H

#include <memory>

class ZCloudReceiveMessageEvent {
public:
    ZCloudReceiveMessageEvent(const std::string& msg, const std::string& topic)
        : msg_(msg),
        topic_(topic) {
    }
public:
    std::string msg() const { return msg_; }
    std::string topic() const { return topic_; }
private:   
    std::string msg_;
    std::string topic_;
};

#endif /* ZCLOUDRECEIVEMESSAGEEVENT_H */

