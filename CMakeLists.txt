cmake_minimum_required(VERSION 3.19)
project(ggj2023 CXX)

find_package(Python COMPONENTS Interpreter REQUIRED)

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

add_subdirectory(assets)
add_subdirectory(engine)
add_subdirectory(src)
add_subdirectory(tests)
