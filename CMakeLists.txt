# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.17 FATAL_ERROR)

project (TSUBAKI-V)

if(WIN32)
	message("BUILD IN PLATEFORM WINDOWS")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message("BUILD DEBUG")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	message("BUILD RELEASE")
endif()

# 包含子项目。
add_executable (TSUBAKI-V "./TSUBAKI-V/TSUBAKI-V.cpp" 
"./TSUBAKI-V/TSUBAKI-V.h")

target_include_directories(TSUBAKI-V PRIVATE "./TSUBAKI-V/include")

add_subdirectory ("3rdpart")


if(CMAKE_BUILD_TYPE MATCHES Debug)
add_custom_command(
    TARGET TSUBAKI-V
    POST_BUILD
    COMMAND copy ${CMAKE_CURRENT_LIST_DIR}\\libs\\Debug\\* ${CMAKE_BINARY_DIR})
elseif(CMAKE_BUILD_TYPE MATCHES Release)
add_custom_command(
    TARGET TSUBAKI-V
    POST_BUILD
    COMMAND copy ${CMAKE_CURRENT_LIST_DIR}\\libs\\Release\\* ${CMAKE_BINARY_DIR})
endif()

