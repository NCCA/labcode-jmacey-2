cmake_minimum_required(VERSION 3.20)

project(Image_build)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem thread)
## RGBA Target
add_executable(Image)
target_include_directories(Image PRIVATE include)
target_sources(Image PRIVATE src/main.cpp src/Image.cpp
include/RGBA.h include/Image.h)

target_link_libraries(Image PRIVATE OpenImageIO::OpenImageIO Boost::filesystem
Boost::thread
)


### Testing Target
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(RGBATests)
target_sources(RGBATests PRIVATE
        test/RGBA_Tests.cpp
        test/Image_tests.cpp
        src/Image.cpp
        include/RGBA.h
        include/Image.h)
target_include_directories(RGBATests PRIVATE include)
target_link_libraries(RGBATests PRIVATE GTest::gtest GTest::gtest_main OpenImageIO::OpenImageIO Boost::filesystem
Boost::thread

)