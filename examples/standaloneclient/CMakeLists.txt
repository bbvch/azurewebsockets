cmake_minimum_required(VERSION 3.1)
set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project (standaloneclient)
set(CMAKE_BUILD_TYPE Release)

set(builddir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR  ${builddir})

set(ROOTDIR ../..)

include_directories(${ROOTDIR}/protocolstack/session/)
include_directories(${ROOTDIR})
add_subdirectory ("${ROOTDIR}" ${builddir}/libazurewebsockets)

file(GLOB CLIENT_SOURCES
    client.cpp
    ${ROOTDIR}/protocolstack/presentation/Message.cpp
    )

add_executable(standaloneclient ${CLIENT_SOURCES})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/session)
target_link_libraries(standaloneclient azurewebsockets)

