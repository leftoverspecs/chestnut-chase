#include "texture.h"

#include <SDL.h>

#include <stdexcept>

namespace engine {

Texture::Binding::Binding(GLenum texture_unit, GLenum target, const Texture &texture)
  : texture_unit(texture_unit), target(target)
{
    glActiveTexture(texture_unit);
    glBindTexture(target, texture.id);
}

Texture::Binding::~Binding() {
    glActiveTexture(texture_unit);
    glBindTexture(target, 0);
}

void Texture::Binding::image_2d(GLint level, GLint internalformat,
                                GLsizei width, GLsizei height, GLint border,
                                GLenum format, GLenum type,
                                const void *data) const
{
    glTexImage2D(target, level, internalformat, width, height, border,
                    format, type, data);
}

void Texture::Binding::set_parameter(GLenum pname, GLint param) const {
    glTexParameteri(target, pname, param);
}

void Texture::Binding::generate_mipmap() const {
    glGenerateMipmap(target);
}

void Texture::Binding::clear(GLint level, GLenum format, GLenum type, const void *data) const {
    glClearTexImage(target, level, format, type, data);
}

Texture::Texture() {
    glGenTextures(1, &id);
}

Texture::Texture(const unsigned char *bmp, std::size_t size)
  : Texture()
{
    SDL_Surface *const surface = SDL_LoadBMP_RW(SDL_RWFromConstMem(bmp, size), 1);
    if (surface == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    auto binding = bind(GL_TEXTURE0, GL_TEXTURE_2D);
    binding.set_parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    binding.set_parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    binding.set_parameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    binding.set_parameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    binding.image_2d(0, GL_RGB, surface->w, surface->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surface->pixels);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

Texture::Binding Texture::bind(GLenum texture_unit, GLenum target) const {
    return Binding(texture_unit, target, *this);
}

}
