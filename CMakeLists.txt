cmake_minimum_required(VERSION 3.14)

project(VideoWriter VERSION 1.0)

set(TARGET videowriter)

if(WIN32)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

set(BUILD_SHARED_LIBS OFF)
add_subdirectory(ext/opencv ${CMAKE_BINARY_DIR}/opencv EXCLUDE_FROM_ALL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GenerateExportHeader)

file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/simulator/*.h)
file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

add_library(${TARGET} SHARED ${HEADERS} ${SOURCES})

string(TOUPPER "${TARGET}_API" export_api)
generate_export_header(
  ${TARGET} EXPORT_MACRO_NAME ${export_api} EXPORT_FILE_NAME
  ${PROJECT_BINARY_DIR}/include/VideoWriterExports.h)

target_link_libraries(${TARGET} PRIVATE opencv_core opencv_highgui
                                        opencv_videoio)

target_include_directories(
  ${TARGET}
  PUBLIC include ${PROJECT_BINARY_DIR}/include
  PRIVATE ext/opencv/modules/core/include ext/opencv/modules/highgui/include
          ext/opencv/modules/imgcodecs/include
          ext/opencv/modules/videoio/include ${CMAKE_BINARY_DIR})

add_executable(demoVideo test/main.cpp)
target_link_libraries(demoVideo videowriter)
