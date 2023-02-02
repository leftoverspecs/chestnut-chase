#pragma once

#include <SDL2/SDL_surface.h>

namespace engine {

class Image {
public:
    Image(const unsigned char *data, std::size_t size);
    ~Image();

    SDL_Surface *get_surface() const { return surface; }
private:
    SDL_Surface *surface;
};

}
