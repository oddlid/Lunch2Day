#cmake_minimum_required (VERSION 2.6)
#project (PBTest)
#
#include(FindProtobuf)
#find_package(Protobuf REQUIRED)
#
#include_directories(${PROTOBUF_INCLUDE_DIR})
#include_directories("/usr/include/jsoncpp/")
#
#SET(CMAKE_CXX_FLAGS "-std=c++11")
#set(CMAKE_EXE_LINKER_FLAGS "-pthread -lprotobuf -pthread -lpthread -ljsoncpp")
#
#add_executable(PBTest pbtest.cc menu.pb.cc)
#
##find_library(JsonCpp)
#
#target_link_libraries(PBTest
#    ${Boost_FILESYSTEM_LIBRARY}
#    ${Boost_SYSTEM_LIBRARY}
#    ${PROTOBUF_LIBRARY}
#)

### New test, for json only ###
cmake_minimum_required (VERSION 2.6)
project (JsonTest)
include_directories("/usr/include/jsoncpp/")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-ljsoncpp")
add_executable(JsonTest jtest.cc)
