project(zcloud)

set(HEADER_FILES ServerApp.h)
set(SOURCE_FILES main.cpp
    ServerApp.cpp
    ${version_file}
)

add_executable(zcloud ${SOURCE_FILES} ${HEADER_FILES})

set(INTERNAL_LIBS
    zworker
    zcommon
    zdb
    zuser
    zdevice
    zadmin
    zsession
    zapihttp.web
    zapihttp
    zapimqtt
    zapicoap
    zapiws
    )

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(EXTERNAL_LIBS /usr/local/opt/openssl/lib/libssl.dylib /usr/local/opt/openssl/lib/libcrypto.dylib)
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(EXTERNAL_LIBS ssl crypto)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

list(APPEND EXTERNAL_LIBS pthread)

find_library(POCOUTIL NAMES PocoUtil)
find_library(POCOJSON NAMES PocoJSON)
find_library(POCOXML NAMES PocoXML)
find_library(POCONET NAMES PocoNet)
find_library(POCOFOUNDATION NAMES PocoFoundation)
set(POCO_LIBS ${POCOUTIL} ${POCOJSON} ${POCOXML} ${POCONET} ${POCOFOUNDATION})

target_link_libraries(zcloud ${EXTERNAL_LIBS} ${INTERNAL_LIBS} ${POCO_LIBS})
