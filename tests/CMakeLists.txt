add_executable(assets_test assets_test.cpp)
target_link_libraries(assets_test PRIVATE assets)

add_executable(wave_test wave_test.cpp)
target_link_libraries(wave_test PRIVATE CONAN_PKG::sdl assets engine)
