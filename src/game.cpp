#include <GL/glew.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_opengl.h>

#include <audio.h>
#include <controller.h>
#include <destination.h>
#include <font.h>
#include <image.h>
#include <music.h>

#include <iostream>
#include <string>

#include <glm/gtc/matrix_transform.hpp>

#include <font.png.h>
#include <logo.png.h>
#include <song.mp3.h>

#include "background.h"
#include "chestnut.h"
#include "health.h"
#include "leaves.h"
#include "player.h"

#ifdef _WIN32
extern "C" {

_declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;

}
#endif

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) != 0) {
        std::cerr << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *const window = SDL_CreateWindow("Chestnut Chase!",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                WIDTH,
                                                HEIGHT,
                                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    engine::Image icon(logo, sizeof(logo));
    SDL_SetWindowIcon(window, icon.get_surface());

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return EXIT_FAILURE;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, WIDTH, HEIGHT);

    engine::Audio audio(44100, MIX_DEFAULT_FORMAT, 2, 128);
    engine::Music music(song, sizeof(song));
    engine::Font font(WIDTH, HEIGHT, test_font, sizeof(test_font));
    engine::Destination destination(WIDTH, HEIGHT);
    engine::Controller controller1(0);
    engine::Controller controller2(1);
    game::Chestnut chestnut(400.0f, 0.5f, 250.0f, WIDTH, HEIGHT);
    game::Health player1_health(true, WIDTH, HEIGHT);
    game::Health player2_health(false, WIDTH, HEIGHT);
    game::Player player1(controller1, player1_health, chestnut, true, 0.0f, 0.0f, WIDTH, HEIGHT);
    game::Player player2(controller2, player2_health, chestnut, false, WIDTH - 50.0f, 0.0f, WIDTH, HEIGHT);
    game::Background background(WIDTH, HEIGHT);
    game::Leaves leaves(WIDTH, HEIGHT);

    bool quit = false;
    long last = SDL_GetTicks64();
    float exposure = 3.2f;
    float gamma = 0.6f;
    //music.play(-1);
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_KP_PLUS:
                    gamma += 0.1f;
                    std::cout << "gamma = " << gamma << '\n';
                    break;
                case SDLK_KP_MINUS:
                    gamma -= 0.1f;
                    std::cout << "gamma = " << gamma << '\n';
                    break;
                case SDLK_PAGEUP:
                    exposure += 0.1f;
                    std::cout << "exposure = " << exposure << '\n';
                    break;
                case SDLK_PAGEDOWN:
                    exposure -= 0.1f;
                    std::cout << "exposure = " << exposure << '\n';
                    break;
                }
                break;
            }
        }
        const long next = SDL_GetTicks64();
        const long diff = next - last;
        last = next;
        {
            auto binding = destination.bind_as_target();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            player1.update(diff);
            player2.update(diff);
            const glm::vec2 mid = 0.5f * (player1.get_position() + player2.get_position());
            background.update(mid.x);
            chestnut.update(diff);

            background.draw();
            player1.draw();
            player2.draw();
            chestnut.draw();
            leaves.draw();
            player1_health.draw();
            player2_health.draw();
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        destination.set_exposure(exposure);
        destination.set_gamma(gamma);
        destination.draw(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        SDL_GL_SwapWindow(window);

        if (diff > 0) {
            const float fps = 1000.0f / (diff);
            SDL_SetWindowTitle(window, std::to_string(fps).c_str());
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
