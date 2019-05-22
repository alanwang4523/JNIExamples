# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(MY_CPP_PATH ${CMAKE_CURRENT_SOURCE_DIR})
message(${ANDROID_ABI})
message(${MY_CPP_PATH})

include_directories(${MY_CPP_PATH})
include_directories(${MY_CPP_PATH}/dynamic/)
include_directories(${MY_CPP_PATH}/static/)
include_directories(${MY_CPP_PATH}/common/)
include_directories(${MY_CPP_PATH}/business/)

file(GLOB_RECURSE CPP_FILES_IN_BUSINESS "${MY_CPP_PATH}/business/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_COMMON "${MY_CPP_PATH}/common/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_DYNAMIC "${MY_CPP_PATH}/dynamic/*.cpp")
file(GLOB_RECURSE CPP_FILES_IN_STATIC "${MY_CPP_PATH}/static/*.cpp")

add_library(
        jni_example
        SHARED

        ${CPP_FILES_IN_BUSINESS}
        ${CPP_FILES_IN_COMMON}
        ${CPP_FILES_IN_DYNAMIC}
        ${CPP_FILES_IN_STATIC}
        )

find_library(
        log-lib
        log)

target_link_libraries( # Specifies the target library.
        jni_example
        ${log-lib})