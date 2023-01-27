#include "spritemap.h"

#include <SDL.h>
#include <SDL_image.h>

#include <stdexcept>

namespace engine {

SpriteMap::SpriteMap(const unsigned char *png, std::size_t size,
                     unsigned int columns, unsigned int rows)
  : columns(columns),
    rows(rows)
{
    SDL_Surface *const surface = IMG_LoadTyped_RW(SDL_RWFromConstMem(png, size), 1, "PNG");
    if (surface == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    auto binding = bind(GL_TEXTURE0, GL_TEXTURE_2D);
    //binding.set_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    //binding.set_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    binding.set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    binding.set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    binding.set_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    binding.set_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    binding.image_2d(0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    sprite_width = static_cast<GLfloat>(surface->w) / columns;
    sprite_height = static_cast<GLfloat>(surface->h) / rows;
}

Texture::Binding SpriteMap::bind(GLenum texture_unit, GLenum target) const {
    return texture.bind(texture_unit, target);
}

SpriteMap::TextureRect SpriteMap::get_sprite(unsigned int i, unsigned j) const {
    const GLfloat fi = static_cast<GLfloat>(i);
    const GLfloat fj = static_cast<GLfloat>(j);
    return TextureRect { fi / columns, fj / rows,
                        (fi + 1.0f) / columns, (fj + 1.0f) / rows };
}

}
