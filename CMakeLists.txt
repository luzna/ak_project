cmake_minimum_required(VERSION 3.5)
project(ak_projekt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(SOURCE_FILES main.cpp Model.cpp Model.h Tests.cpp Tests.h )
add_executable(ak_projekt ${SOURCE_FILES})