add_executable(chestnutchase WIN32
    background.cpp
    background.h
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
