#include "wave.h"

#include <cassert>
#include <stdexcept>

namespace engine {

Wave::Wave(const std::string &filename) {
    if (SDL_LoadWAV(filename.c_str(), &spec, &buffer, &length) == nullptr) {
        throw std::runtime_error("Can't load wave file " + filename);
    }
}

Wave::Wave(const unsigned char *data, std::size_t size) {
    if (SDL_LoadWAV_RW(SDL_RWFromConstMem(data, size), 1, &spec, &buffer, &length) == nullptr) {
        throw std::runtime_error("Can't load wave file from memoy");
    }
}

Wave::~Wave() {
    SDL_FreeWAV(buffer);
}

const SDL_AudioSpec &Wave::get_spec() const {
    return spec;
}

const Uint8 *Wave::get_buffer() const {
    return buffer;
}

Uint32 Wave::get_length() const {
    return length;
}

std::vector<Uint8> Wave::convert_to_spec(const SDL_AudioSpec &destination) const {
    SDL_AudioCVT cvt;
    SDL_BuildAudioCVT(&cvt, spec.format, spec.channels, spec.freq, destination.format, destination.channels, destination.freq);
    cvt.len = length;
    std::vector<Uint8> result(cvt.len * cvt.len_mult);
    cvt.buf = result.data();
    assert(SDL_ConvertAudio(&cvt) == 0);
    return result;
}

}
