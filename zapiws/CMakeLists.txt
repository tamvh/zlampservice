project(zapiws)

set(HEADER_DIR "include/zapiws")
set(PRIVATE_HEADER_DIR "private/include")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZApiWS.h
)

set(PRIVATE_HEADER_FILES
    ${PRIVATE_HEADER_DIR}/ClientInfo.h
    ${PRIVATE_HEADER_DIR}/RequestHandlerFactory.h
    ${PRIVATE_HEADER_DIR}/WebSocketMessage.h
    ${PRIVATE_HEADER_DIR}/PageRequestHandler.h
    ${PRIVATE_HEADER_DIR}/ServerPacket.h
    ${PRIVATE_HEADER_DIR}/WebSocketRequestHandler.h
)

set(SOURCE_FILES
    ${SRC_DIR}/ClientInfo.cpp
    ${SRC_DIR}/PageRequestHandler.cpp
    ${SRC_DIR}/RequestHandlerFactory.cpp
    ${SRC_DIR}/ServerPacket.cpp
    ${SRC_DIR}/WebSocketMessage.cpp
    ${SRC_DIR}/WebSocketRequestHandler.cpp
    ${SRC_DIR}/ZApiWS.cpp
    ${SRC_DIR}/ZApiWS_EventHandlers.cpp
)

add_library(zapiws STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PRIVATE_HEADER_FILES})
