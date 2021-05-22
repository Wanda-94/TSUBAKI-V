# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("TSUBAKI-V")

if(WIN32)
	message("BUILD IN PLATEFORM WINDOWS")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message("BUILD DEBUG")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
	message("BUILD RELEASE")
endif()

# 包含子项目。
add_subdirectory ("TSUBAKI-V")
