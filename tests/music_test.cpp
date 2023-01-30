#include <SDL.h>

#include <audio.h>
#include <chunk.h>
#include <music.h>

#include <iostream>
#include <cstdlib>

#include <test_music.mp3.h>
#include <blib.wav.h>

int main(int argc, char *argv[]) {
    setenv("ALSA_CONFIG_DIR", "/usr/share/alsa", 1);
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    engine::Audio audio(44100, MIX_DEFAULT_FORMAT, 2, 128);
    engine::Music music(test_music, sizeof(test_music));
    engine::Chunk chunk(blib, sizeof(blib));

    static const int width = 800;
    static const int height = 600;

    SDL_Window *const window = SDL_CreateWindow("visualizer",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width,
                                                height,
                                                SDL_WINDOW_SHOWN);
    SDL_Renderer *const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    bool playing = false;
    while (!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_SPACE:
                    if (!playing) {
                        music.play(-1);
                        playing = true;
                    } else {
                        music.halt();
                        playing = false;
                    }
                    break;
                case SDLK_RETURN:
                    chunk.play(0);
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
