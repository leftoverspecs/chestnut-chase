#include <SDL.h>

#include <cassert>

#include <assets.h>
#include <wave.h>

int main() {
    assert(SDL_Init(SDL_INIT_AUDIO) == 0);
    Wave wav(ASSETS_DIRECTORY "/blib.wav");
    return 0;
}
