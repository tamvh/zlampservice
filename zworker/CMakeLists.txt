project(zworker)

set(HEADER_DIR "include/zworker")
set(PRIVATE_HEADER_DIR "private/include")
set(SRC_DIR "src")

include_directories(private/include)

set(HEADER_FILES
    ${HEADER_DIR}/ZWorker.h
    ${HEADER_DIR}/ZDeviceDataUpdatedEvent.h
    ${HEADER_DIR}/ZDeviceDataCreatedEvent.h
    ${HEADER_DIR}/ZDeviceDataDeletedEvent.h
    ${HEADER_DIR}/ZDeviceDataChangeInformationEvent.h
    ${HEADER_DIR}/ZCloudReceiveMessageEvent.h
)

set(PRIVATE_HEADER_FILES
    ""
)

set(SOURCE_FILES
    ${SRC_DIR}/ZWorker.cpp
    ${SRC_DIR}/ZWorkerUsers.cpp
#    ${SRC_DIR}/ZDeviceDataUpdatedEvent.cpp
)

add_library(zworker STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PRIVATE_HEADER_FILES})
