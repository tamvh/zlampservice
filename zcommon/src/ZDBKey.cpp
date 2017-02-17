#include <sstream>
#include "zcommon/ZDBKey.h"

std::string ZDBKey::generatorUsers() {
    return "users";
}

std::string ZDBKey::UserApiKey() {
    return "users:lookup:apikey";
}

std::string ZDBKey::UserEmail() {
    return "users:lookup:email";
}

std::string ZDBKey::UserSet() {
    return "users:set";
}

std::string ZDBKey::UserEntry(int32_t userId) {
    std::stringstream stream;
    stream << "users:" << userId;
    return stream.str();
}

std::string ZDBKey::apiKey() {
    return "apikey";
}

std::string ZDBKey::UserSession(int32_t userId) {
    std::stringstream stream;
    stream << "users:" << userId << ":sessions";
    return stream.str();
}

std::string ZDBKey::CoffeeLog(){
    
}
