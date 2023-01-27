#pragma once

#include "spritemap.h"
#include "spriterenderer.h"

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

namespace engine {

class Font {
public:
    Font(GLfloat width, GLfloat height, const unsigned char *png, std::size_t size);

    void clear();
    void write(glm::mat4 model, const glm::vec4 &color, const char *text);
    void draw();

    int get_width() const { return sprites.get_sprite_width(); }
    int get_height() const { return sprites.get_sprite_height(); }
private:
    SpriteMap sprites;
    SpriteRenderer renderer;
};

}
