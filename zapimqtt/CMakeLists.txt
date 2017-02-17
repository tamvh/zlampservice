project(zapimqtt)

set(HEADER_DIR "include/zapimqtt")
set(PRIVATE_HEADER_DIR "private/include")
set(SRC_DIR "src")
set(MQTT_PAHO_SRC_DIR "private/paho/src")
set(MQTT_PAHO_INCLUDE_DIR "private/paho/include")

include_directories(${PRIVATE_HEADER_DIR})
include_directories(${MQTT_PAHO_INCLUDE_DIR})

# for openssl
include_directories(/usr/local/opt/openssl/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZApiMQTT.h
    ${HEADER_DIR}/MqttClientWorker.h
    ${HEADER_DIR}/MqttTopic.h
)

set(PRIVATE_FILES
    ${PRIVATE_HEADER_DIR}/message.h
    ${PRIVATE_HEADER_DIR}/messagebus.h
    ${PRIVATE_HEADER_DIR}/mqttbus.h
)

set(SOURCE_FILES
    ${SRC_DIR}/ZApiMQTT.cpp
    ${SRC_DIR}/message.cpp
    ${SRC_DIR}/messagebus.cpp
    ${SRC_DIR}/mqttbus.cpp
    ${SRC_DIR}/mqttbusimpl.cpp
    ${SRC_DIR}/mqttbusimpl.h
    ${SRC_DIR}/MqttClientWorker.cpp
    ${SRC_DIR}/MqttTopic.cpp
)

set(MQTT_PAHO_FILES
    ${MQTT_PAHO_SRC_DIR}/Clients.c
    ${MQTT_PAHO_SRC_DIR}/MQTTPacket.c
    ${MQTT_PAHO_SRC_DIR}/MQTTVersion.c
    ${MQTT_PAHO_SRC_DIR}/Thread.c
    ${MQTT_PAHO_SRC_DIR}/Heap.c
    ${MQTT_PAHO_SRC_DIR}/MQTTPacketOut.c
    ${MQTT_PAHO_SRC_DIR}/Messages.c
    ${MQTT_PAHO_SRC_DIR}/Tree.c
    ${MQTT_PAHO_SRC_DIR}/LinkedList.c
    ${MQTT_PAHO_SRC_DIR}/MQTTPersistence.c
    ${MQTT_PAHO_SRC_DIR}/SSLSocket.c
    ${MQTT_PAHO_SRC_DIR}/utf-8.c
    ${MQTT_PAHO_SRC_DIR}/Log.c
    ${MQTT_PAHO_SRC_DIR}/MQTTPersistenceDefault.c
    ${MQTT_PAHO_SRC_DIR}/Socket.c
    ${MQTT_PAHO_SRC_DIR}/MQTTAsync.c
    ${MQTT_PAHO_SRC_DIR}/MQTTProtocolClient.c
    ${MQTT_PAHO_SRC_DIR}/SocketBuffer.c
    ${MQTT_PAHO_SRC_DIR}/MQTTClient.c
    ${MQTT_PAHO_SRC_DIR}/MQTTProtocolOut.c
    ${MQTT_PAHO_SRC_DIR}/StackTrace.c

    ${MQTT_PAHO_INCLUDE_DIR}/MQTTAsync.h
    ${MQTT_PAHO_INCLUDE_DIR}/MQTTClient.h
    ${MQTT_PAHO_INCLUDE_DIR}/MQTTClientPersistence.h
)

add_definitions(-DOPENSSL)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
add_definitions(-DUSE_NAMED_SEMAPHORES -Wno-deprecated-declarations)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_library(zapimqtt STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PRIVATE_FILES} ${MQTT_PAHO_FILES})
