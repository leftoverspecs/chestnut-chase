add_library(engine STATIC
    audio.h
    audio.cpp
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
    CONAN_PKG::sdl
    CONAN_PKG::sdl_image
    CONAN_PKG::glew
    assets
)
target_link_libraries(engine PUBLIC CONAN_PKG::glm CONAN_PKG::sdl_mixer)
target_include_directories(engine INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_features(engine PUBLIC cxx_std_17)
