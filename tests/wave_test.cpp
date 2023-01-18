#include <SDL.h>

#include <cassert>

#include <wave.h>
#include <blib.wav.h>

int main() {
    assert(SDL_Init(SDL_INIT_AUDIO) == 0);
    Wave wav(blib, sizeof(blib));
    return 0;
}
