#pragma once

#include "texture.h"

namespace engine {

class SpriteMap {
public:
    SpriteMap(const unsigned char *png, std::size_t size,
              unsigned int columns, unsigned int rows);

    Texture::Binding bind(GLenum texture_unit, GLenum target) const;

    struct TextureRect {
        GLfloat u_min;
        GLfloat v_min;
        GLfloat u_max;
        GLfloat v_max;
    };

    TextureRect get_sprite(unsigned int i, unsigned j) const;

    GLfloat get_sprite_width() const { return sprite_width; }
    GLfloat get_sprite_height() const { return sprite_height; }
private:
    Texture texture;
    GLfloat sprite_width;
    GLfloat sprite_height;
    GLfloat columns;
    GLfloat rows;
};

}
