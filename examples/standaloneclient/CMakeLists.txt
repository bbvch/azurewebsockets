cmake_minimum_required(VERSION 2.8)
set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

project (standaloneclient)
set(CMAKE_BUILD_TYPE Release)

set(builddir ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BINARY_DIR  ${builddir})

set(ROOTDIR ../..)

find_path(INCLUDE_DIRECTORIES libazurewebsockets ${YOCTO_INCLUDE_PATH})
if(NOT INCLUDE_DIRECTORIES)
message("--->heeeere--->${YOCTO_INCLUDE_PATH}")
message(FATAL_ERROR "Did not find the include directory")
endif(NOT INCLUDE_DIRECTORIES)
include_directories(${INCLUDE_DIRECTORIES}/libazurewebsockets)

find_library(sharedlibs azurewebsockets websockets ${YOCTO_LIBRARY_PATH})
if(NOT sharedlibs)
    message(FATAL_ERROR "Did not find the required libraries azurewebsockets and websockets")
endif(NOT sharedlibs)



file(GLOB CLIENT_SOURCES
    client.cpp
    ${ROOTDIR}/protocolstack/presentation/Message.cpp
    )

add_executable(standaloneclient ${CLIENT_SOURCES})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/session)
target_link_libraries(standaloneclient ${sharedlibs})

install(TARGETS standaloneclient DESTINATION bin)

#Set Flags has to be at bottom to overwrite above set default rules
#set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -std=c++14")
