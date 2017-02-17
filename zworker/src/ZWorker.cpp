#include <Poco/RegularExpression.h>

#include <zcommon/ZServiceLocator.h>
#include <zcommon/StringUtil.h>
#include <zcommon/ZDBKey.h>

#include <zsession/ZSessionService.h>

#include "zworker/ZDeviceEvent.h"
#include <zworker/ZWorker.h>

ZWorker::ZWorker() {
}

ZWorker::~ZWorker() {
}

bool ZWorker::initialize() {
    return true;
}

bool ZWorker::start() {
    return true;
}

bool ZWorker::stop() {
    return true;
}

bool ZWorker::cleanup() {
    return true;
}


ZWorkerResult ZWorker::ChooseCoffee(int32_t type) {
    ZDeviceEvent event(type);
    chooseCoffeeEvent(this, event);
    return ZWorkerResult(event);
}

ZWorkerResult ZWorker::writeLogChooseCoffee(const std::string& username) {
    
}

