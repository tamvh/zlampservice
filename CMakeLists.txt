cmake_minimum_required(VERSION 3.0)
project(zcloud)

set(CMAKE_CXX_STANDARD 11)

# Appends the cmake/modules path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#
# Make a version file containing the current version from git.
#
include(GetGitRevisionDescription)
git_describe(VERSION --tags --dirty=-dirty)

MESSAGE( STATUS "VERSION:         " ${VERSION} )
#parse the version information into pieces.
string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.cpp.in
                ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")


include_directories(zdb/include)
include_directories(zadmin/include)
include_directories(zuser/include)
include_directories(zdevice/include)
include_directories(zsession/include)
include_directories(zcommon/include)
include_directories(zcommon/include/msgpack)
include_directories(zapihttp/include)
include_directories(zapihttp.web/include)
include_directories(zapimqtt/include)
include_directories(zapicoap/include)
include_directories(zapiws/include)
include_directories(zworker/include)

add_subdirectory(zdb)
add_subdirectory(zadmin)
add_subdirectory(zuser)
add_subdirectory(zdevice)
add_subdirectory(zsession)
add_subdirectory(zcommon)
add_subdirectory(zapihttp)
add_subdirectory(zapihttp.web)
add_subdirectory(zapimqtt)
add_subdirectory(zapicoap)
add_subdirectory(zapiws)
add_subdirectory(zworker)

add_subdirectory(zcloud)

add_subdirectory(testscripts)

