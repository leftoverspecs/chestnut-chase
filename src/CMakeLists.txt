add_executable(game WIN32
    game.cpp
    player.cpp
    player.h
)
target_link_libraries(game PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)
