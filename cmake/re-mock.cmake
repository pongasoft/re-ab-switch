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

include(FetchContent)

if(RE_MOCK_ROOT_DIR)
  # instructs FetchContent to not download or update but use the location instead
  set(FETCHCONTENT_SOURCE_DIR_RE-MOCK ${RE_MOCK_ROOT_DIR})
else()
  set(FETCHCONTENT_SOURCE_DIR_RE-MOCK "")
endif()

set(RE_MOCK_GIT_REPO "https://github.com/pongasoft/re-mock" CACHE STRING "re-mock git repository url")
set(RE_MOCK_GIT_TAG "v1.0.0" CACHE STRING "re-mock git tag")

FetchContent_Declare(re-mock
      GIT_REPOSITORY    ${RE_MOCK_GIT_REPO}
      GIT_TAG           ${RE_MOCK_GIT_TAG}
      GIT_CONFIG        advice.detachedHead=false
      GIT_SHALLOW       true
      SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/re-mock"
      BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/re-mock-build"
      CONFIGURE_COMMAND ""
      BUILD_COMMAND     ""
      INSTALL_COMMAND   ""
      TEST_COMMAND      ""
      )

FetchContent_GetProperties(re-mock)

if(NOT re-mock_POPULATED)

  if(FETCHCONTENT_SOURCE_DIR_RE-MOCK)
    message(STATUS "Using re-mock from local ${FETCHCONTENT_SOURCE_DIR_RE-MOCK}")
  else()
    message(STATUS "Fetching re-mock ${RE_MOCK_GIT_REPO}/tree/${RE_MOCK_GIT_TAG}")
  endif()

  FetchContent_Populate(re-mock)

endif()

set(RE_MOCK_ROOT_DIR ${re-mock_SOURCE_DIR})

# re-mock is a library to link with
add_subdirectory("${re-mock_SOURCE_DIR}" "${re-mock_BINARY_DIR}" EXCLUDE_FROM_ALL)
