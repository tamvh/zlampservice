project(zsession)

set(HEADER_DIR "include/zsession")
set(HEADER_PRIVATE_DIR "private/include")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZSessionService.h
)

set(HEADER_PRIVATE_FILES
    ${HEADER_PRIVATE_DIR}/aes256.h
    ${HEADER_PRIVATE_DIR}/base64url.h
    ${HEADER_PRIVATE_DIR}/sessiondata.h
)

set(SOURCE_FILES
    ${SRC_DIR}/aes256.c
    ${SRC_DIR}/base64url.cpp
    ${SRC_DIR}/sessiondata.cpp
    ${SRC_DIR}/ZSessionService.cpp
)

add_library(zsession STATIC ${SOURCE_FILES} ${HEADER_FILES} ${HEADER_PRIVATE_FILES})
