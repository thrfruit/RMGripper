cmake_minimum_required(VERSION 3.10)
project(autoTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(autoTest main.cpp Serial.cpp Serial.h)
find_package(Threads REQUIRED)
target_link_libraries(autoTest Threads::Threads)
