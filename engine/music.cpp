#include "music.h"

#include <stdexcept>

namespace engine {

Music::Music(const unsigned char *data, std::size_t size)
  : music(Mix_LoadMUS_RW(SDL_RWFromConstMem(data, size), 1))
{
    if (music == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

Music::~Music() {
    Mix_FreeMusic(music);
}

void Music::play(int loops) const {
    if (Mix_PlayMusic(music, loops) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

void Music::halt() const {
    Mix_HaltMusic();
}

}
