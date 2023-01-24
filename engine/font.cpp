#include "font.h"

namespace engine {

Font::Font(GLfloat width, GLfloat height, const unsigned char *png, std::size_t size) 
  : sprites(png, size, 16, 8),
    renderer(sprites, width, height)
{ }

void Font::clear() {
    renderer.clear();
}

void Font::write(int x, int y, const char *text) {
    for (const char *c = text; *c != '\0'; ++c) {
        unsigned int i = *c & 0x0f;
        unsigned int j = (*c >> 4) & 0x0f;
        renderer.queue(x, y, sprites.get_sprite_width(), sprites.get_sprite_height(), i, j);
        x += sprites.get_sprite_width();
    }
}

void Font::draw() {
    renderer.draw();
}

}
