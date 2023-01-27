#include "font.h"

#include <glm/gtx/transform.hpp>

namespace engine {

Font::Font(GLfloat width, GLfloat height, const unsigned char *png, std::size_t size) 
  : sprites(png, size, 16, 8),
    renderer(sprites, width, height)
{ }

void Font::clear() {
    renderer.clear();
}

void Font::write(glm::mat4 model, const glm::vec4 &color, const char *text) {
    const glm::mat4 t = glm::translate(glm::vec3(1.0f, 0.0f, 0.0f));
    for (const char *c = text; *c != '\0'; ++c) {
        unsigned int i = *c & 0x0f;
        unsigned int j = (*c >> 4) & 0x0f;
        renderer.queue(model, color, i, j);
        model = model * t;
    }
}

void Font::draw() {
    renderer.draw();
}

}
