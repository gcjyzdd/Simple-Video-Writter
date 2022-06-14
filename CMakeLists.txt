cmake_minimum_required(VERSION 3.14)

project(VideoWriter VERSION 1.3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

set(BUILD_SHARED_LIBS OFF)
set(BUILD_WITH_STATIC_CRT OFF)
add_subdirectory(ext/opencv ${CMAKE_BINARY_DIR}/opencv EXCLUDE_FROM_ALL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(GenerateExportHeader)

file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/simulator/*.h)
file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

set(TARGET videowriter)

add_library(${TARGET} SHARED ${HEADERS} ${SOURCES})

string(TOUPPER "${TARGET}_API" export_api)
generate_export_header(
  ${TARGET} EXPORT_MACRO_NAME ${export_api} EXPORT_FILE_NAME
  ${PROJECT_BINARY_DIR}/include/videowriter/VideoWriterExports.h)

target_link_libraries(${TARGET} PRIVATE opencv_core opencv_highgui
                                        opencv_videoio)

target_include_directories(
  ${TARGET}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
         $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
         $<INSTALL_INTERFACE:include>
  PRIVATE ext/opencv/modules/core/include ext/opencv/modules/highgui/include
          ext/opencv/modules/imgcodecs/include
          ext/opencv/modules/videoio/include ${CMAKE_BINARY_DIR})

install(
  TARGETS videowriter
  DESTINATION lib
  EXPORT videowriterTargets)
install(TARGETS videowriter RUNTIME DESTINATION bin)
install(FILES include/simulator/vedeowriterAPI.h
              ${PROJECT_BINARY_DIR}/include/videowriter/VideoWriterExports.h
        DESTINATION include/videowriter)
if(WIN32)
  install(
    FILES ${PROJECT_BINARY_DIR}/bin/Release/opencv_videoio_ffmpeg452_64.dll
    DESTINATION bin)
endif()

install(
  EXPORT videowriterTargets
  FILE videowriterTargets.cmake
  DESTINATION lib/cmake/videowriter)

include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/videowriterConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO NO_CHECK_REQUIRED_COMPONENTS_MACRO)
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/videowriterConfigVersion.cmake"
  VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion)

# install the configuration file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/videowriterConfig.cmake
        DESTINATION lib/cmake/videowriter)
# project to also be used from a build directory
export(EXPORT videowriterTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/videowriterTargets.cmake")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
include(CPack)

add_executable(demoVideo test/main.cpp)
target_link_libraries(demoVideo videowriter)
