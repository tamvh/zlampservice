/*
 * File:   ZApiHTTPRequestBaseHandler.cpp
 * Author: huuhoa
 *
 * Created on November 8, 2015, 9:11 AM
 */

#include <stdint.h>
#include <sstream>

#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Struct.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>

#include <zcommon/ZServiceLocator.h>
#include <zsession/ZSessionService.h>

#include <zapihttp/ZApiHTTPRequestBaseHandler.h>

using namespace Poco::JSON;
using namespace Poco::Dynamic;

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

using Poco::Util::Application;

ZApiHTTPRequestBaseHandler::ZApiHTTPRequestBaseHandler(const std::string& requestPath)
: _requestPath(requestPath) {
}

ZApiHTTPRequestBaseHandler::~ZApiHTTPRequestBaseHandler() {
}

Poco::Dynamic::Var ZApiHTTPRequestBaseHandler::parseServerRequest(Poco::Net::HTTPServerRequest& request,
        Poco::JSON::Object::Ptr& responseData) {

    std::istream& istr = request.stream();

    std::string requestBody = std::string(std::istreambuf_iterator<char>(istr), {});

    Poco::Dynamic::Var emptyResult;

    if (requestBody.empty()) {
        ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
        return emptyResult;
    }

    Parser parser;
    try {
        Var result = parser.parse(requestBody);
        if (result.type() != typeid (Object::Ptr)) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return emptyResult;
        }

        Object::Ptr object = result.extract<Object::Ptr>();
        if (object->size() == 0) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return emptyResult;
        }

        return result;
    } catch (Poco::Exception &ex) {
        Application& app = Application::instance();
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return emptyResult;
    }
}

int32_t ZApiHTTPRequestBaseHandler::getAuthenticatedUser(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) const {
    std::string authToken = request.get("Authorization", std::string());
    if (authToken.empty()) {
        ReportError::reportTo(HttpApiError::AuthenticationMissing, responseData);
        return -1;
    }
    const std::string bearer("Bearer ");
    if (!(authToken.compare(0, bearer.length(), bearer) == 0)) {
        ReportError::reportTo(HttpApiError::AuthenticationMissing, responseData);
        return -1;
    }
    authToken = authToken.substr(bearer.length());
    ZSessionService* sessionService = ZServiceLocator::instance()->
            get<ZSessionService>(ZServiceLocator::ServiceId::SessionService);
    int32_t userId;
    ZErrorCode errorCode = sessionService->validate_jwt(authToken, userId);
    if (errorCode != ZErrorCode::OK) {
        ReportError::reportTo(static_cast<HttpApiError> (errorCode), responseData);
        return -1;
    }
    return userId;
}

std::string ZApiHTTPRequestBaseHandler::getAuthenticationToken(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) const {
    std::string authToken = request.get("Authorization", std::string());
    if (authToken.empty()) {
        ReportError::reportTo(HttpApiError::AuthenticationMissing, responseData);
        return std::string();
    }
    const std::string bearer("Bearer ");
    if (!(authToken.compare(0, bearer.length(), bearer) == 0)) {
        ReportError::reportTo(HttpApiError::AuthenticationMissing, responseData);
        return std::string();
    }
    authToken = authToken.substr(bearer.length());
    return authToken;
}

