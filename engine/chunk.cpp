#include "chunk.h"

#include <stdexcept>

namespace engine {

Chunk::Chunk(const unsigned char *data, std::size_t size)
  : chunk(Mix_LoadWAV_RW(SDL_RWFromConstMem(data, size), 1))
{
    if (chunk == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}

Chunk::~Chunk() {
    Mix_FreeChunk(chunk);
}

void Chunk::play(int loops) const {
    if (Mix_PlayChannel(-1, chunk, loops) == -1) {
        throw std::runtime_error(SDL_GetError());
    }
}

}
