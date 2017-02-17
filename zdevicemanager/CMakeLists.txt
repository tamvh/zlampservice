project(zuser)

set(HEADER_DIR "include/zuser")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZUserInfo.h
    ${HEADER_DIR}/ZUserManager.h
)

set(SOURCE_FILES
    ${SRC_DIR}/ZUserInfo.cpp
    ${SRC_DIR}/ZUserManager.cpp
)

add_library(zuser STATIC ${SOURCE_FILES} ${HEADER_FILES})
