add_executable(chestnutchase WIN32
    background.cpp
    background.h
    chestnut.cpp
    chestnut.h
    chestnuts.cpp
    chestnuts.h
    game.cpp
    health.cpp
    health.h
    leaves.cpp
    leaves.h
    player.cpp
    player.h
    score.cpp
    score.h
)
target_link_libraries(chestnutchase PRIVATE
    CONAN_PKG::sdl
    CONAN_PKG::glew
    assets
    engine
)
