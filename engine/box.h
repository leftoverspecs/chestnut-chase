#pragma once

#include "buffer.h"
#include "program.h"
#include "vertexarray.h"

namespace engine {

class Box {
public:
    Box(float x, float y, float w, float h, float screen_width, float screen_height);

    void relocate(float x, float y);
    void resize(float w, float h);

    bool collides_with_box(const Box &other) const;

    void draw(glm::vec4 color);
    void draw_filled(glm::vec4 color);

private:
    Program shader;
    VertexArray vao;
    Buffer vertex_buffer;
    
    float x;
    float y;
    float w;
    float h;
};

}
