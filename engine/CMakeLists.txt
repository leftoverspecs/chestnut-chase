add_library(engine STATIC
    audio.h
    audio.cpp
    box.h
    box.cpp
    buffer.h
    buffer.cpp
    chunk.h
    chunk.cpp
    controller.h
    controller.cpp
    destination.h
    destination.cpp
    font.h
    font.cpp
    framebuffer.h
    framebuffer.cpp
    image.h
    image.cpp
    keyboard.h
    keyboard.cpp
    music.h
    music.cpp
    particles.h
    particles.cpp
    program.h
    program.cpp
    quad.h
    quad.cpp
    renderbuffer.h
    renderbuffer.cpp
    shader.cpp
    shader.h
    spritemap.cpp
    spritemap.h
    spriterenderer.cpp
    spriterenderer.h
    texture.h
    texture.cpp
    vertexarray.h
    vertexarray.cpp
    wave.h
    wave.cpp
)
target_link_libraries(engine PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    GLEW::glew
    assets
)
target_link_libraries(engine PUBLIC glm::glm SDL2_mixer::SDL2_mixer OpenGL::GL)
target_include_directories(engine INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(engine PUBLIC cxx_std_17)
