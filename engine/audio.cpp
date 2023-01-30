#include "audio.h"

#include <SDL_mixer.h>

#include <iostream>
#include <stdexcept>

namespace engine {

Audio::Audio(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

Audio::~Audio() {
    Mix_CloseAudio();
}

}
