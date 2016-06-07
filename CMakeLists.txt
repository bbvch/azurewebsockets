cmake_minimum_required(VERSION 3.1)
set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
add_definitions(-DNO_LOGGING)
set (use_wsio ON CACHE INTERNAL "")
set (skip_unittests ON CACHE INTERNAL "")
project (azurewebsockets)
set(CMAKE_BUILD_TYPE Release)
set(rootdir ${CMAKE_CURRENT_SOURCE_DIR}../../)

file(GLOB RAW_SOURCES
    *.h
    protocolstack/*.h
    protocolstack/*.cpp

    protocolstack/presentation/*.cpp
    protocolstack/presentation/*.h
    protocolstack/application/*.cpp
    protocolstack/application/*.h
    protocolstack/application/message/*.h
    protocolstack/application/message/*.cpp
    infrastructure/*.cpp
    infrastructure/*.h
    infrastructure/cli/*.cpp
    infrastructure/cli/*.h
    infrastructure/concurrency/*.cpp
    infrastructure/concurrency/*.h
    )

file(GLOB SAS_SOURCES
    ${rootdir}/infrastructure/SasToken.cpp
    ${rootdir}/infrastructure/SasToken.h
    ${rootdir}/infrastructure/cli/PocoParser.cpp
    ${rootdir}/infrastructure/cli/PocoParser.h
    )

file(GLOB SESSION_SOURCES
    infrastructure/SasToken.cpp
    infrastructure/SasToken.h
    infrastructure/concurrency/Timer.cpp
    infrastructure/concurrency/Timer.h
    protocolstack/presentation/Message.cpp
    protocolstack/presentation/Message.h
    protocolstack/session/*.cpp
    protocolstack/session/*.h
    protocolstack/session/mqtt/*.h
    protocolstack/session/mqtt/*.cpp
    protocolstack/session/http/*.h
    protocolstack/session/http/*.cpp
    protocolstack/session/amqp/AmqpSession.cpp
    protocolstack/session/amqp_websockets/iothub_certs.c
    )


#include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/amqp/azure-iot-sdks/c/iothub_client/inc/")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/azure-c-shared-utility/c/inc")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/inc")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/protocolstack/session/iothub_certs)
include_directories (".")

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/" EXCLUDE_FROM_ALL)

#add_library(azurewebsockets STATIC
add_library(azurewebsockets SHARED
protocolstack/session/AzureAmqpWs.cpp 
protocolstack/session/Factory.cpp 
protocolstack/session/iothub_certs/iothub_certs.c
infrastructure/SasToken.cpp
)
target_link_libraries(azurewebsockets pthread PocoUtil jsoncpp PocoFoundation uamqp ssl crypto crypto++ uamqp aziotsharedutil websockets_shared uuid)
set_target_properties(azurewebsockets PROPERTIES VERSION ${Main_VERSION_MAJOR}                                            SOVERSION ${Main_VERSION_MAJOR})
install(TARGETS azurewebsockets DESTINATION lib )

