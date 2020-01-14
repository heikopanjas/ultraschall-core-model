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

set(PUBLIC_INCLUDE_PATH ../include)

set(PUBLIC_INCLUDES
  ${PUBLIC_INCLUDE_PATH}/CoreCommon.h
  ${PUBLIC_INCLUDE_PATH}/CoreFx.h
  ${PUBLIC_INCLUDE_PATH}/CoreGlobals.h
  ${PUBLIC_INCLUDE_PATH}/CoreGuid.h
  ${PUBLIC_INCLUDE_PATH}/CoreService.h
  ${PUBLIC_INCLUDE_PATH}/CoreServiceManager.h
  ${PUBLIC_INCLUDE_PATH}/CoreStream.h
  ${PUBLIC_INCLUDE_PATH}/CoreString.h
  ${PUBLIC_INCLUDE_PATH}/CoreStringArray.h
  ${PUBLIC_INCLUDE_PATH}/CoreStringBuilder.h
  ${PUBLIC_INCLUDE_PATH}/CoreStringDictionary.h
  ${PUBLIC_INCLUDE_PATH}/CoreStringFunctions.h
  ${PUBLIC_INCLUDE_PATH}/CoreSharedObject.h
  ${PUBLIC_INCLUDE_PATH}/CoreWideString.h
)

set(PRIVATE_INCLUDES
  Common.h
  Platform.h
  ServiceFactory.h
  ServiceRegistry.h
)

set(PRIVATE_SOURCES
  ServiceFactory.cpp
  CoreServiceManager.cpp
  ServiceRegistry.cpp
  CoreStream.cpp
  CoreString.cpp
  CoreStringArray.cpp
  CoreStringBuilder.cpp
  CoreStringDictionary.cpp
  CoreStringFunctions.cpp
  CoreSharedObject.cpp
  CoreWideString.cpp
)

set(PLATFORM_INCLUDES FileDialog.h Platform.h)
set(PLATFORM_SOURCES
  # ${ULTRASCHALL_TARGET_SYSTEM}/FileDialog.cpp
  ${ULTRASCHALL_TARGET_SYSTEM}/Platform.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR})

if(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "win32")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  set(EXTRA_SOURCES win32/version.rc)
  set(EXTRA_LIBRARIES version.lib ws2_32.lib crypt32.lib wldap32.lib mfplat.lib mf.lib mfuuid.lib shlwapi.lib comctl32.lib comdlg32.lib rpcrt4.lib)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "macos")
  add_compile_options(-mmacosx-version-min=10.11)
  set_source_files_properties(macos/Platform.cpp macos/FileDialog.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
  set(EXTRA_LIBRARIES "-framework AppKit" "-framework Carbon" "-framework IOKit" "-framework Security")
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "linux")
endif()

message(STATUS "PRIVATE_INCLUDES  = ${PRIVATE_INCLUDES}")
message(STATUS "PRIVATE_SOURCES   = ${PRIVATE_SOURCES}")
message(STATUS "PUBLIC_INCLUDES   = ${PUBLIC_INCLUDES}")
message(STATUS "PLATFORM_INCLUDES = ${PLATFORM_INCLUDES}")
message(STATUS "PLATFORM_SOURCES  = ${PLATFORM_SOURCES}")
message(STATUS "EXTRA_INCLUDES    = ${EXTRA_INCLUDES}")
message(STATUS "EXTRA_SOURCES     = ${EXTRA_SOURCES}")

source_group("Header Files" FILES ${PRIVATE_INCLUDES} ${PUBLIC_INCLUDES} ${PLATFORM_INCLUDES})
source_group("Source Files" FILES ${PRIVATE_SOURCES} ${PLATFORM_SOURCES})
source_group("External Files" FILES ${EXTRA_INCLUDES} ${EXTRA_SOURCES})

add_library(ultraschall-core
  ${PRIVATE_INCLUDES}
  ${PRIVATE_SOURCES}
  ${PUBLIC_INCLUDES}
  ${PLATFORM_INCLUDES}
  ${PLATFORM_SOURCES}
  ${EXTRA_INCLUDES}
  ${EXTRA_SOURCES}
)

target_link_libraries(ultraschall-core ${EXTRA_LIBRARIES})
set_target_properties(ultraschall-core PROPERTIES PREFIX "")
