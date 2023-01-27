#pragma once

#include "buffer.h"
#include "program.h"
#include "vertexarray.h"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <vector>

namespace engine {

class SpriteMap;
class Texture;

class SpriteRenderer {
public:
    SpriteRenderer(const SpriteMap &map, GLfloat width, GLfloat height);

    void clear();
    void queue(const glm::mat4 &model, const glm::vec4 &color,
               unsigned int i, unsigned int j);
    void draw() const;
private:
    Program shader;
    VertexArray vao;
    Buffer vertex_buffer;
    const SpriteMap &map;
    std::vector<GLfloat> batch;
};

}
