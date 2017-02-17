project(zcommon)

set(HEADER_DIR "include/zcommon")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ErrorCode.h
    ${HEADER_DIR}/StringUtil.h
    ${HEADER_DIR}/ZMemProxy.h
    ${HEADER_DIR}/ZMemProxyLocal.h
    ${HEADER_DIR}/ZServiceInterface.h
    ${HEADER_DIR}/ZServiceLocator.h
    ${HEADER_DIR}/version.h
    ${HEADER_DIR}/ZDBKey.h
)

set(SOURCE_FILES
    ${SRC_DIR}/StringUtil.cpp
    ${SRC_DIR}/ZMemProxy.cpp
    ${SRC_DIR}/ZMemProxyLocal.cpp
    ${SRC_DIR}/ZServiceLocator.cpp
    ${SRC_DIR}/ZDBKey.cpp
)

add_library(zcommon STATIC ${SOURCE_FILES} ${HEADER_FILES})
