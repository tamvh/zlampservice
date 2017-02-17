/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZCoffeeMachineChooseEvent.h
 * Author: tamvh
 *
 * Created on April 13, 2016, 11:33 AM
 */

#ifndef ZCOFFEEMACHINECHOOSEEVENT_H
#define ZCOFFEEMACHINECHOOSEEVENT_H

#include <memory>

class ZDeviceEvent {
public:
    ZDeviceEvent(int32_t type)
        : _type(type) {
    }
public:
    int32_t type() const { return _type; }
private:   
    int32_t _type;
};

#endif /* ZCOFFEEMACHINECHOOSEEVENT_H */

