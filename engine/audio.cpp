#include "audio.h"

#include <SDL_mixer.h>

#include <cstdlib>
#include <stdexcept>

namespace engine {

#ifndef WIN32
namespace {

class AlsaEnv {
public:
    AlsaEnv() {
#ifndef WIN32
        setenv("ALSA_CONFIG_DIR", "/usr/share/alsa", 1);
#endif
    }
} alsa_env;

}
#endif

Audio::Audio(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
}

Audio::~Audio() {
    Mix_CloseAudio();
}

}
