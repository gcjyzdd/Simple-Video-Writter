cmake_minimum_required(VERSION 3.1)
project(test_package)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CONAN_WXWIDGET_ROOT}")

find_package(videowriter REQUIRED)

add_executable(${PROJECT_NAME} example.cpp)
target_link_libraries(${PROJECT_NAME} videowriter)
