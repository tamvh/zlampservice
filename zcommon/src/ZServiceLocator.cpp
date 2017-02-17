/* 
 * File:   ZServiceLocator.cpp
 * Author: huuhoa
 * 
 * Created on October 27, 2015, 3:32 PM
 */

#include "zcommon/ZServiceLocator.h"

ZServiceLocator* ZServiceLocator::_instance = 0;

ZServiceLocator::ZServiceLocator() {
}

ZServiceLocator* ZServiceLocator::instance() {
    if (_instance == 0) {
        _instance = new ZServiceLocator();
    }
    
    return _instance;
}

void ZServiceLocator::registerService(ServiceId serviceId, void* service) {
    auto iter = _services.find(serviceId);
    if (iter == _services.end()) {
        _services[serviceId] = service;
    }
}
