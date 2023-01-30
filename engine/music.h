#pragma once

#include <SDL_mixer.h>

#include <cstddef>

namespace engine {

class Music {
public:
    Music(const unsigned char *data, std::size_t size);
    ~Music();
    
    void play(int loops) const;
    void halt() const;
private:
    Mix_Music *music;
};

}
