cmake_minimum_required(VERSION 3.20)
project(AutoPlugin)

set(CMAKE_CXX_STANDARD 14)


find_package(realsense2 REQUIRED)
find_package(ur_rtde REQUIRED)
find_package(OpenCV REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(AutoPlugin
        main.cpp
        src/gripper_driver.cpp)


include_directories(include ${realsense_INCLUDE_DIR} )
target_include_directories(AutoPlugin PRIVATE ${realsense_INCLUDE_DIR} )
target_link_libraries(AutoPlugin PRIVATE ${realsense2_LIBRARY} ${OpenCV_LIBS} ur_rtde::rtde Eigen3::Eigen)


add_executable(test
        test.cpp
        src/gripper_driver.cpp)


target_include_directories(test PRIVATE ${realsense_INCLUDE_DIR} )
target_link_libraries(test PRIVATE ${realsense2_LIBRARY} ${OpenCV_LIBS} ur_rtde::rtde Eigen3::Eigen)

add_executable(virtual_paint virtual_paint.cpp)
target_include_directories(virtual_paint PRIVATE ${realsense_INCLUDE_DIR} )
target_link_libraries(virtual_paint ${realsense2_LIBRARY} ${OpenCV_LIBS} ur_rtde::rtde Eigen3::Eigen)

add_executable(color_picker color_picker.cpp)
target_include_directories(color_picker PRIVATE ${realsense_INCLUDE_DIR} )
target_link_libraries(color_picker ${realsense2_LIBRARY} ${OpenCV_LIBS} ur_rtde::rtde Eigen3::Eigen)


add_executable(imgCapture calibration_imgCapture.cpp)
target_include_directories(imgCapture PRIVATE ${realsense_INCLUDE_DIR})
target_link_libraries(imgCapture ${realsense2_LIBRARY} ${OpenCV_LIBS} ur_rtde::rtde Eigen3::Eigen)