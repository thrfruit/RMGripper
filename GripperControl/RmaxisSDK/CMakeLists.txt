# CMake  minimum version required
cmake_minimum_required(VERSION 3.17)
# Project information
project(RmaxisSDK)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)

add_subdirectory(libmodbus)
include_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
link_directories(./lib)
link_directories(./libmodbus)
add_executable(RmaxisSDK ${DIR_SRCS})
# AD采集卡链接库
target_link_libraries(RmaxisSDK -l_usbdaq_v20 -lusb-1.0)

target_link_libraries(RmaxisSDK modbus)