add_executable(assets_test assets_test.cpp)
target_link_libraries(assets_test PRIVATE test_assets)

add_executable(wave_test wave_test.cpp)
target_link_libraries(wave_test PRIVATE SDL2::SDL2 SDL2::SDL2main test_assets engine)

add_executable(sprite_test sprite_test.cpp)
target_link_libraries(sprite_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(spritemap_test spritemap_test.cpp)
target_link_libraries(spritemap_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(font_test WIN32 font_test.cpp)
target_link_libraries(font_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(particle_test particle_test.cpp)
target_link_libraries(particle_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(transparency_test transparency_test.cpp)
target_link_libraries(transparency_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(destination_test destination_test.cpp)
target_link_libraries(destination_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)

add_executable(music_test WIN32 music_test.cpp)
target_link_libraries(music_test PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    GLEW::GLEW
    test_assets
    engine
)
