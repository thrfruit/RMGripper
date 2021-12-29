cmake_minimum_required(VERSION 3.20)
project(SMSBL)

set(CMAKE_CXX_STANDARD 14)
include_directories(./lib)
link_directories(./lib)
link_libraries(libSCServo.a)
file(GLOB hdrs *h)
file(GLOB srs *.cpp)

add_executable(SMSBL main.cpp ${hdrs} ${srs})

find_package(Threads)
target_link_libraries(SMSBL ${CMAKE_THREAD_LIBS_INIT})