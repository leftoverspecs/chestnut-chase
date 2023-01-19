add_executable(assets_test assets_test.cpp)
target_link_libraries(assets_test PRIVATE assets)

add_executable(wave_test wave_test.cpp)
target_link_libraries(wave_test PRIVATE CONAN_PKG::sdl assets engine)

add_executable(sprite_test sprite_test.cpp)
target_link_libraries(sprite_test PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)

add_executable(spritemap_test spritemap_test.cpp)
target_link_libraries(spritemap_test PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)

add_executable(font_test font_test.cpp)
target_link_libraries(font_test PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)

add_executable(transparency_test transparency_test.cpp)
target_link_libraries(transparency_test PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)
