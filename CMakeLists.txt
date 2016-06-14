cmake_minimum_required(VERSION 2.8.0)
set (Main_VERSION_MAJOR 0)
set (Main_VERSION_MINOR 1)
include(CheckCXXCompilerFlag)

add_definitions(-DNO_LOGGING)
set (use_wsio ON CACHE INTERNAL "")
set (skip_unittests ON CACHE INTERNAL "")
project (azurewebsockets)
set(CMAKE_BUILD_TYPE Release)
set(rootdir ${CMAKE_CURRENT_SOURCE_DIR}../../)

file(GLOB AZUREWEBSOCKETS_SOURCES
    infrastructure/SasToken.cpp
    infrastructure/SasToken.h
    protocolstack/session/*.cpp
    protocolstack/session/*.h
    azure-uamqp-c/samples/websockets_sample/iothub_certs.c
    )

file(GLOB LIBRARY_HEADERS
    protocolstack/session/*.h
    protocolstack/presentation/*.h
    )

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/azure-c-shared-utility/inc")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/inc/azure_uamqp_c")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/inc")
include_directories (".")

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/azure-uamqp-c/" EXCLUDE_FROM_ALL)

add_library(azurewebsockets SHARED ${AZUREWEBSOCKETS_SOURCES})
find_library(poco_path PocoFoundation )
find_library(cryptopp_path crypto++)
if((NOT poco_path) OR (NOT cryptopp_path))
    message(FATAL_ERROR "Did not find the required libraries PocoFoundation and crypto++ to build libazurewebsockets")
endif((NOT poco_path) OR (NOT cryptopp_path))
target_link_libraries(azurewebsockets ${poco_path} ${cryptopp_path} uamqp aziotsharedutil websockets_shared )
set_target_properties(azurewebsockets PROPERTIES VERSION ${Main_VERSION_MAJOR} SOVERSION ${Main_VERSION_MAJOR})
install(TARGETS azurewebsockets DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/azure-uamqp-c/libuamqp.so DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/azure-uamqp-c/libwebsockets/lib/libwebsockets.so DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/azure-uamqp-c/libwebsockets/lib/libwebsockets.so.6 DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/azure-uamqp-c/azure-c-shared-utility/libaziotsharedutil.so DESTINATION lib)
install(DIRECTORY protocolstack infrastructure DESTINATION include/libazurewebsockets FILES_MATCHING PATTERN "*.h")

#Check if compiler supports c++14
CHECK_CXX_COMPILER_FLAG(-std=c++14 compiler_supports_cpp14)
if(NOT compiler_supports_cpp14)
    message(FATAL_ERROR "Compiler does not seem to support needed c++14 flag")
endif(NOT compiler_supports_cpp14)

#Set Flags has to be at bottom to overwrite above set default rules
#Use newer CMAKE_CXX_STANDARD setting on new cmake-versions, fallback to setting it in CXX_FLAGS
if( ${CMAKE_VERSION} VERSION_GREATER "3.1")
    set_property(TARGET azurewebsockets PROPERTY CXX_STANDARD 14)
else( ${CMAKE_VERSION} VERSION_GREATER "3.1")
    message("Cmake version smaller than 3.1 - fallback to adding c++14 flag")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -std=c++14")
endif( ${CMAKE_VERSION} VERSION_GREATER "3.1")
