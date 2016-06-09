cmake_minimum_required(VERSION 3.1)
set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

project (standaloneclient)
set(CMAKE_BUILD_TYPE Release)

set(builddir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR  ${builddir})

set(ROOTDIR ../..)

include_directories(${ROOTDIR}/protocolstack/session/)
include_directories(${ROOTDIR})
find_library(sharedlibs azurewebsockets websockets /usr/local/lib/azurewebsockets ${YOCTO_LIBRARY_PATH})
if(NOT sharedlibs)
    #message("Libs path: ${YOCTO_LIBRARY_PATH}")
    essage(FATAL_ERROR "Did not find the required libraries azurewebsockets and websockets")
endif(NOT sharedlibs)

file(GLOB CLIENT_SOURCES
    client.cpp
    ${ROOTDIR}/protocolstack/presentation/Message.cpp
    )

add_executable(standaloneclient ${CLIENT_SOURCES})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/session)
#target_link_libraries(standaloneclient azurewebsockets uamqp aziotsharedutil websockets_shared)
target_link_libraries(standaloneclient ${sharedlibs})

install(TARGETS standaloneclient DESTINATION bin)

#Set Flags has to be at bottom to overwrite above set default rules
#set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -std=c++14")
