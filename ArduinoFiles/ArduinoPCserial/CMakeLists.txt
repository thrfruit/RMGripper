cmake_minimum_required(VERSION 3.20)
project(ArduinoPCserial)

set(CMAKE_CXX_STANDARD 14)

add_executable(ArduinoPCserial echo.cpp easy_serial.h Serial.cpp Serial.h)
