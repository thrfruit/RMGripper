# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/zoukai/Downloads/clion-2021.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/zoukai/Downloads/clion-2021.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zoukai/ros/AutoPlugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zoukai/ros/AutoPlugin/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/virtual_paint.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/virtual_paint.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/virtual_paint.dir/flags.make

CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o: CMakeFiles/virtual_paint.dir/flags.make
CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o: ../virtual_paint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zoukai/ros/AutoPlugin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o -c /home/zoukai/ros/AutoPlugin/virtual_paint.cpp

CMakeFiles/virtual_paint.dir/virtual_paint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/virtual_paint.dir/virtual_paint.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zoukai/ros/AutoPlugin/virtual_paint.cpp > CMakeFiles/virtual_paint.dir/virtual_paint.cpp.i

CMakeFiles/virtual_paint.dir/virtual_paint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/virtual_paint.dir/virtual_paint.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zoukai/ros/AutoPlugin/virtual_paint.cpp -o CMakeFiles/virtual_paint.dir/virtual_paint.cpp.s

# Object files for target virtual_paint
virtual_paint_OBJECTS = \
"CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o"

# External object files for target virtual_paint
virtual_paint_EXTERNAL_OBJECTS =

virtual_paint: CMakeFiles/virtual_paint.dir/virtual_paint.cpp.o
virtual_paint: CMakeFiles/virtual_paint.dir/build.make
virtual_paint: /usr/local/lib/librealsense2.so.2.49.0
virtual_paint: /usr/local/lib/libopencv_gapi.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_stitching.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_aruco.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_barcode.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_bgsegm.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_bioinspired.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_ccalib.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_dnn_objdetect.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_dnn_superres.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_dpm.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_face.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_freetype.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_fuzzy.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_hfs.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_img_hash.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_intensity_transform.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_line_descriptor.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_mcc.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_quality.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_rapid.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_reg.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_rgbd.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_saliency.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_stereo.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_structured_light.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_superres.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_surface_matching.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_tracking.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_videostab.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_wechat_qrcode.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_xfeatures2d.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_xobjdetect.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_xphoto.so.4.5.4
virtual_paint: /usr/local/lib/librtde.so.1.4.8
virtual_paint: /usr/local/lib/libopencv_shape.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_highgui.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_datasets.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_plot.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_text.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_ml.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_phase_unwrapping.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_optflow.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_ximgproc.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_video.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_videoio.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_imgcodecs.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_objdetect.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_calib3d.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_dnn.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_features2d.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_flann.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_photo.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_imgproc.so.4.5.4
virtual_paint: /usr/local/lib/libopencv_core.so.4.5.4
virtual_paint: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
virtual_paint: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
virtual_paint: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
virtual_paint: CMakeFiles/virtual_paint.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zoukai/ros/AutoPlugin/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable virtual_paint"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/virtual_paint.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/virtual_paint.dir/build: virtual_paint
.PHONY : CMakeFiles/virtual_paint.dir/build

CMakeFiles/virtual_paint.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/virtual_paint.dir/cmake_clean.cmake
.PHONY : CMakeFiles/virtual_paint.dir/clean

CMakeFiles/virtual_paint.dir/depend:
	cd /home/zoukai/ros/AutoPlugin/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zoukai/ros/AutoPlugin /home/zoukai/ros/AutoPlugin /home/zoukai/ros/AutoPlugin/cmake-build-debug /home/zoukai/ros/AutoPlugin/cmake-build-debug /home/zoukai/ros/AutoPlugin/cmake-build-debug/CMakeFiles/virtual_paint.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/virtual_paint.dir/depend

