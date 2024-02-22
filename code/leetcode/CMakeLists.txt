# 最低CMake版本要求
cmake_minimum_required(VERSION 3.0)

# 设置项目名称
project(leetcode)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# 添加可执行文件
# add_executable(leetcode src/main.cpp)
add_executable(leetcode ${SOURCE_FILES})