################################################################################
#
# Copyright (c) The Ultraschall Project (https://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

cmake_minimum_required(VERSION 3.12)
project(ultraschall-core-fx VERSION 4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(ULTRASCHALL_TARGET_SYSTEM "win32")
elseif(APPLE)
    set(ULTRASCHALL_TARGET_SYSTEM "macos")
elseif(UNIX)
  execute_process(COMMAND uname -a RESULT_VARIABLE UNAME_RESULT OUTPUT_VARIABLE UNAME_OUTPUT OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(UNAME_RESULT EQUAL 0)
    if(${UNAME_OUTPUT} MATCHES "[A|a]rch")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[U|u]buntu")
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[M|m]icrosoft") # WSL
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    elseif(${UNAME_OUTPUT} MATCHES "[A|a]zure") # Azure DevOps
        set(ULTRASCHALL_TARGET_SYSTEM "linux")
    else()
      message(STATUS "Unsupported platform: " ${UNAME_OUTPUT})
      message(FATAL_ERROR "Supported platforms are Windows, macOS, Arch Linux and Ubuntu Linux")
    endif()
  else()
    message(FATAL_ERROR "Failed to run uname, result: ${UNAME_RESULT}")
  endif()
endif()

include(cmake/GlobalArgs.cmake)

message(STATUS "ULTRASCHALL_TARGET_SYSTEM = " ${ULTRASCHALL_TARGET_SYSTEM})
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${ULTRASCHALL_TARGET_SYSTEM}.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_SHARED_LIBS CACHE OFF)

if(BUILD_SHARED_LIBS)
  add_definitions(-DULTRASCHALL_CORE_SHARED)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

