#include "box.h"

#include <box.frag.h>
#include <box.vert.h>

namespace engine {

namespace {

const int ATTRIBUTE_POSITION = 0;

}

Box::Box(float x, float y, float w, float h, float screen_width, float screen_height)
  : x(x), y(y), w(w), h(h)
{
    shader.attach(Shader(GL_VERTEX_SHADER, reinterpret_cast<const char *>(box_vert), sizeof(box_vert)));
    shader.attach(Shader(GL_FRAGMENT_SHADER, reinterpret_cast<const char *>(box_frag), sizeof(box_frag)));
    shader.bind(ATTRIBUTE_POSITION, "position");
    shader.link();

    {
        auto usage = shader.use();
        usage.set_uniform("width", screen_width);
        usage.set_uniform("height", screen_height);
    }
    {
        auto binding = vao.bind();
        binding.enable_attribute(ATTRIBUTE_POSITION);

        auto buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
        buffer_binding.vertex_attrib_pointer(binding, ATTRIBUTE_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, (void *)(0 * sizeof(GLfloat)));
        buffer_binding.data(16 * sizeof(GLfloat), nullptr, GL_DYNAMIC_DRAW);
    }
}

void Box::relocate(float x, float y) {
    this->x = x;
    this->y = y;
}

void Box::resize(float w, float h) {
    this->w = w;
    this->h = h;
}

bool Box::collides_with_box(const Box &other) const {
    const bool horizontal_overlap
        = (x < other.x && other.x < x + w)
            || (other.x < x && x < other.x + other.w);
    const bool vertical_overlap
        = (y < other.y && other.y < y + h)
            || (other.y < y && y < other.y + other.h);
    return horizontal_overlap && vertical_overlap;
}

void Box::draw(glm::vec4 color) {
    const GLfloat data[] = {
        x,     y,     x + w, y,
        x + w, y,     x + w, y + h,
        x + w, y + h, x,     y + h,
        x,     y + h, x,     y
    };
    auto usage = shader.use();
    usage.set_uniform("color", color);
    auto binding = vao.bind();
    auto buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
    buffer_binding.subdata(0, sizeof(data), data);
    //void *d = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    //glUnmapBuffer(GL_ARRAY_BUFFER);
    glDrawArrays(GL_LINES, 0, 16);
}

void Box::draw_filled(glm::vec4 color) {
    const GLfloat data[] = {
        x, y, x + w, y,     x + w, y + h,
        x, y, x,     y + h, x + w, y + h
    };
    auto usage = shader.use();
    usage.set_uniform("color", color);
    auto binding = vao.bind();
    auto buffer_binding = vertex_buffer.bind(GL_ARRAY_BUFFER);
    buffer_binding.subdata(0, sizeof(data), data);
    //void *d = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    //glUnmapBuffer(GL_ARRAY_BUFFER);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

}
