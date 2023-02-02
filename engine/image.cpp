#include "image.h"

#include <SDL_image.h>

#include <stdexcept>

namespace engine {

Image::Image(const unsigned char *data, std::size_t size)
  : surface(IMG_LoadTyped_RW(SDL_RWFromConstMem(data, size), 1, "PNG"))
{
    if (surface == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

Image::~Image() {
    SDL_FreeSurface(surface);
}

}
