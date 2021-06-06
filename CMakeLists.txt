# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.17 FATAL_ERROR)

project (TSUBAKI-V)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

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
"./TSUBAKI-V/TSUBAKI-V.h" 
"TSUBAKI-V/source/GlobalSetting/GlobalSetting.cpp" "TSUBAKI-V/include/RHI/RHI.h" "TSUBAKI-V/source/RHI/RHI.cpp" "TSUBAKI-V/source/Engine/Engine.cpp" "TSUBAKI-V/include/Engine/Engine.h" "TSUBAKI-V/source/WindowSystem/WindowSystem.cpp" "TSUBAKI-V/include/WindowSystem/WindowSystem.h" "TSUBAKI-V/include/Log/Log.h" "TSUBAKI-V/source/Log/Log.cpp" "TSUBAKI-V/include/GlobalSetting/IncludeFile.h")

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

