add_executable(chestnutchase WIN32
    game.cpp
    player.cpp
    player.h
)
target_link_libraries(chestnutchase PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)
