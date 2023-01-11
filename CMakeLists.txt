cmake_minimum_required(VERSION 3.19)
project(ggj2023 CXX)

set(ASSETS_DIRECTORY "${CMAKE_INSTALL_PREFIX}/share/labyrinth/assets" CACHE PATH "Directory for game assets")

include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup(TARGETS)

add_subdirectory(assets)
add_subdirectory(engine)
add_subdirectory(src)
add_subdirectory(tests)
