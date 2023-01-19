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
private:
    Texture texture;
    GLfloat columns;
    GLfloat rows;
};

}
