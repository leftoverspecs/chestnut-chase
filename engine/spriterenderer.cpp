#include "spriterenderer.h"

#include "texture.h"

#include <stdexcept>

#include <sprite.vert.h>
#include <sprite.frag.h>

namespace engine {

namespace {

const std::vector<GLfloat>::size_type CAPACITY = 10000 * 4;
const int ATTRIBUTE_POSITION = 0;
const int ATTRIBUTE_TEXTURE_COORD = 1;

}

SpriteRenderer::SpriteRenderer(const Texture &texture, GLfloat width, GLfloat height)
  : texture(texture)
{
    shader.attach(Shader(GL_VERTEX_SHADER, reinterpret_cast<const char *>(sprite_vert), sizeof(sprite_vert)));
    shader.attach(Shader(GL_FRAGMENT_SHADER, reinterpret_cast<const char *>(sprite_frag), sizeof(sprite_frag)));
    shader.bind(ATTRIBUTE_POSITION, "position");
    shader.bind(ATTRIBUTE_TEXTURE_COORD, "texture_coord");
    shader.link();

    {
        auto usage = shader.use();
        usage.set_uniform("width", width);
        usage.set_uniform("height", height);
        usage.set_uniform("sprite_texture", 0);
    }
    {
        auto binding = vao.bind();
        binding.enable_attribute(ATTRIBUTE_POSITION);
        binding.enable_attribute(ATTRIBUTE_TEXTURE_COORD);

        auto buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
        buffer_binding.vertex_attrib_pointer(binding, ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(0 * sizeof(GLfloat)));
        buffer_binding.vertex_attrib_pointer(binding, ATTRIBUTE_TEXTURE_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void *)(2 * sizeof(GLfloat)));
        buffer_binding.data(CAPACITY * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    }
    batch.reserve(CAPACITY);
}

void SpriteRenderer::queue(GLfloat x, GLfloat y, GLfloat width, GLfloat height) {
    const GLfloat data[] = {
        x,         y,          0, 0,
        x + width, y,          1, 0,
        x + width, y + height, 1, 1,
        

        x,         y,          0, 0,
        x,         y + height, 0, 1,
        x + width, y + height, 1, 1,
    };
    if (batch.size() + 6 * 4 >= CAPACITY) {
        throw std::runtime_error("Can't queue any further sprite");
    }
    batch.insert(batch.end(), data, data + sizeof(data) / sizeof(data[0]));
}

void SpriteRenderer::draw() const {
    auto usage = shader.use();
    auto texture_binding = texture.bind(GL_TEXTURE0, GL_TEXTURE_2D);
    auto binding = vao.bind();
    auto buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
    buffer_binding.subdata(0, batch.size() * sizeof(GLfloat), batch.data());
    //void *data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    //glUnmapBuffer(GL_ARRAY_BUFFER);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(batch.size()));
}

}
