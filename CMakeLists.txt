cmake_minimum_required(VERSION 3.20)
project(PixaForge VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 第三方库
add_subdirectory(third_party)

# 引擎库
add_subdirectory(engine)

# 游戏可执行文件
add_subdirectory(game)

# 工具（可选构建）
option(BUILD_TOOLS "Build engine tools" ON)
if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()
