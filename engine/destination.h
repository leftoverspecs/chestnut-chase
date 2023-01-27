#pragma once

#include "buffer.h"
#include "framebuffer.h"
#include "program.h"
#include "renderbuffer.h"
#include "texture.h"
#include "vertexarray.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <stdexcept>

namespace engine {

class Destination {
public:
    class Exception : public std::runtime_error {
    public:
        Exception(const char *message) : std::runtime_error(message) { }
    };

    Destination(GLsizei width, GLsizei height);

    Framebuffer::Binding bind_as_target() const;

    void draw(const glm::mat4x4 &projection, const glm::vec3 &color) const;

private:
    Program shader;
    GLsizei width;
    GLsizei height;
    Framebuffer framebuffer;
    Texture destination;
    Renderbuffer depth_stencil;
    VertexArray vao;
    Buffer screen_vertices;
};

}
