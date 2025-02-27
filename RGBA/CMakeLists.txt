cmake_minimum_required(VERSION 3.20)

project(RGBA_build)

set(CMAKE_CXX_STANDARD 17)

## RGBA Target
add_executable(RGBA)
target_include_directories(RGBA PRIVATE include)
target_sources(RGBA PRIVATE src/main.cpp)

### Testing Target
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(RGBATests)
target_sources(RGBATests PRIVATE test/RGBA_Tests.cpp)
target_include_directories(RGBATests PRIVATE include)
target_link_libraries(RGBATests PRIVATE GTest::gtest)