#pragma once

#include "spritemap.h"
#include "spriterenderer.h"

namespace engine {

class Font {
public:
    Font(GLfloat width, GLfloat height, const unsigned char *png, std::size_t size);

    void write(int x, int y, const char *text);

    int get_height() const { return sprites.get_sprite_height(); }
private:
    SpriteMap sprites;
    SpriteRenderer renderer;
};

}
