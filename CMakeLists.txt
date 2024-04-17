cmake_minimum_required(VERSION 3.10)  # 指定CMake的最低版本要求

project(dwf)  # 设置项目名称

# 添加可执行文件，并指定源文件
add_executable(dfs main.cpp dwf.cpp)

# 设置头文件路径，这样编译器就能找到头文件
target_include_directories(dfs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
