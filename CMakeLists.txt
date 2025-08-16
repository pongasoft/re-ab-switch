# Copyright (c) 2020 pongasoft
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#
# @author Yan Pujante

cmake_minimum_required(VERSION 3.13)

# Capturing root of project
set(RE_PROJECT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Using RE SDK version 4.2.0
set(RE_SDK_VERSION 4.6.0)

include(cmake/options.cmake)  # (optional) override versions used
include(cmake/re-cmake.cmake) # include re-cmake (BEFORE project() definition)

# Setting up project (note that the version is defined in lua.info)
project(re-ab-switch LANGUAGES CXX)

# Using C++17
set(CMAKE_CXX_STANDARD 17)

# Initializes re-cmake (re-mock for unit testing)
re_cmake_init(INCLUDES re-logging re-mock)

# Defining where the sources of the plugin live
set(RE_CPP_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src/cpp")

# Defining all the source files for the project
# Although you could use a file(GLOB ...) pattern, it is NOT recommended
# as the CMake generation would happen on every single build!
set(re_sources_cpp
    ${RE_CPP_SRC_DIR}/ABAudioSwitch.cpp
    ${RE_CPP_SRC_DIR}/ABAudioSwitch.h
    ${RE_CPP_SRC_DIR}/ABCVSwitch.cpp
    ${RE_CPP_SRC_DIR}/ABCVSwitch.h
    ${RE_CPP_SRC_DIR}/ABSwitch.cpp
    ${RE_CPP_SRC_DIR}/ABSwitch.h
    ${RE_CPP_SRC_DIR}/AudioSocket.cpp
    ${RE_CPP_SRC_DIR}/AudioSocket.h
    ${RE_CPP_SRC_DIR}/CVSocket.cpp
    ${RE_CPP_SRC_DIR}/CVSocket.h
    ${RE_CPP_SRC_DIR}/Constants.h
    ${RE_CPP_SRC_DIR}/Device.cpp
    ${RE_CPP_SRC_DIR}/Device.h
    ${RE_CPP_SRC_DIR}/DeviceState.cpp
    ${RE_CPP_SRC_DIR}/DeviceState.h
    ${RE_CPP_SRC_DIR}/JBoxProperty.cpp
    ${RE_CPP_SRC_DIR}/JBoxProperty.h
    ${RE_CPP_SRC_DIR}/JBoxPropertyObserver.cpp
    ${RE_CPP_SRC_DIR}/JBoxPropertyObserver.h
    ${RE_CPP_SRC_DIR}/JukeboxExports.cpp
    )

# Defining where the local GUI2D files live
set(RE_2D_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/GUI2D")

# Defining all the 2D source files
# Although you could use a file(GLOB ...) pattern, it is NOT recommended
# as the CMake generation would happen on every single build!
set(re_sources_2d

    # lua files describing the GUI
    ${RE_2D_SRC_DIR}/device_2D.lua
    ${RE_2D_SRC_DIR}/hdgui_2D.lua

    # Images for the device
    ${RE_2D_SRC_DIR}/81x14_5x5.png
    ${RE_2D_SRC_DIR}/Cable_Attachment_CV_01_1frames.png
    ${RE_2D_SRC_DIR}/Cable_Attachment_Audio_01_1frames.png
    ${RE_2D_SRC_DIR}/Placeholder.png
    ${RE_2D_SRC_DIR}/Reason_GUI_back_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_GUI_back_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_audio_ledA_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_audio_ledB_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_audio_soundOnLED_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_audio_switch_scaled_knob.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_cv_ledA_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_cv_ledB_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_cv_switch_scaled_knob.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_audio_ledA_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_audio_ledB_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_audio_soundOnLED_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_audio_switch_scaled_knob.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_audio_xfade_button.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_cv_ledA_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_cv_ledB_lamp.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_cv_switch_scaled_knob.png
    ${RE_2D_SRC_DIR}/Reason_GUI_front_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Icon128x128_back_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Icon128x128_back_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Icon128x128_front_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Icon128x128_front_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Navigator_back_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Navigator_back_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Navigator_front_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Navigator_front_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Palette_back_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Palette_back_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Palette_front_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_Palette_front_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_TrackListIcon_back_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_TrackListIcon_back_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_TrackListIcon_front_folded_root_panel.png
    ${RE_2D_SRC_DIR}/Reason_TrackListIcon_front_root_panel.png
    ${RE_2D_SRC_DIR}/Tape_Horizontal_1frames.png
    )

# Location of the test cases
set(TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/test/cpp")

# List of test cases
set(re_test_cpp
    "${TEST_DIR}/test-Device.cpp"
    )

# Adding the RE plugin
add_re_plugin(
    RE_SDK_VERSION         "${RE_SDK_VERSION}"
    RE_SDK_ROOT            "${RE_SDK_ROOT}"
    RE_2D_RENDER_ROOT      "${RE_2D_RENDER_ROOT}"
    BUILD_SOURCES          "${re_sources_cpp}"
    NATIVE_BUILD_SOURCES   "${re-logging_SOURCES}"
    RENDER_2D_SOURCES      "${re_sources_2d}"
    INCLUDE_DIRECTORIES    "${re-logging_INCLUDE_DIRS}"
    #   COMPILE_OPTIONS        -Wall
    #   NATIVE_COMPILE_OPTIONS -Wall                     # Ok for macOS, try -W4 instead for Windows/Clang
    JBOX_COMPILE_OPTIONS   -Wall
    ENABLE_DEBUG_LOGGING                             # turn on JBOX_TRACE and loguru

    # Testing
    TEST_CASE_SOURCES        "${re_test_cpp}"        # the source files containing the test cases
    TEST_INCLUDE_DIRECTORIES "${RE_CPP_SRC_DIR}"     # tests include plugin classes
    TEST_LINK_LIBS           "native-test-lib" "${re-mock_LIBRARY_NAME}"  # tests link with plugin classes and re-mock
)
