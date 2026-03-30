cmake_minimum_required (VERSION 3.8)
project(FortRemakeCpp)

# 自动搜索所有文件
file(GLOB_RECURSE MY_SOURCES src/*.cpp)
file(GLOB_RECURSE MY_HEADERS include/*.h)

# 创建项目
add_executable(FortRemakeCpp ${MY_SOURCES} ${MY_HEADERS})

# 让 VS 能跳转、能找到头文件（关键）
target_include_directories(FortRemakeCpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# C++20
set_property(TARGET FortRemakeCpp PROPERTY CXX_STANDARD 20)