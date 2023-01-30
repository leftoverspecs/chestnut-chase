#pragma once

#include <SDL_mixer.h>

#include <cstddef>

namespace engine {

class Chunk {
public:
    Chunk(const unsigned char *data, std::size_t size);
    ~Chunk();

    void play(int loops) const;
private:
    Mix_Chunk *chunk;
};

}
