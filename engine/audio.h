#pragma once

#include <SDL.h>

#include <functional>

namespace engine {

class Audio {
public:
    explicit Audio(int frequency, Uint16 format, int channels, int chunksize);
    ~Audio();
};

}
