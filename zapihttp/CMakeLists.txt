project(zapihttp)

set(HEADER_DIR "include/zapihttp")
set(HEADER_PRIVATE_DIR "private/include")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZApiHTTP.h
    ${HEADER_DIR}/ZApiHTTPRequestBaseHandler.h
)

set(HEADER_PRIVATE_FILES
    ${HEADER_PRIVATE_DIR}/TimeRequestHandler.h
    ${HEADER_PRIVATE_DIR}/VersionRequestHandler.h
    ${HEADER_PRIVATE_DIR}/ZApiHTTPAdminRequestHandler.h
    ${HEADER_PRIVATE_DIR}/ZApiHTTPDeviceRequestHandler.h
    ${HEADER_PRIVATE_DIR}/ZApiHTTPRequestHandlerFactory.h
    ${HEADER_PRIVATE_DIR}/ZApiHTTPUserRequestHandler.h
)

set(SOURCE_FILES
    ${SRC_DIR}/TimeRequestHandler.cpp
    ${SRC_DIR}/VersionRequestHandler.cpp
    ${SRC_DIR}/ZApiHTTP.cpp
    ${SRC_DIR}/ZApiHTTPAdminRequestHandler.cpp
    ${SRC_DIR}/ZApiHTTPDeviceRequestHandler.cpp
    ${SRC_DIR}/ZApiHTTPRequestBaseHandler.cpp
    ${SRC_DIR}/ZApiHTTPRequestHandlerFactory.cpp
    ${SRC_DIR}/ZApiHTTPUserRequestHandler.cpp
)

add_library(zapihttp STATIC ${SOURCE_FILES} ${HEADER_FILES} ${HEADER_PRIVATE_FILES})
