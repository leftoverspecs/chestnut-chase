#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <particles.h>

#include <iostream>

#include <test_particle.png.h>

#ifdef _WIN32
extern "C" {

_declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;

}
#endif

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
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

    static const int width = 800;
    static const int height = 600;

    SDL_Window *const window = SDL_CreateWindow("visualizer",
                                                SDL_WINDOWPOS_CENTERED,
                                                SDL_WINDOWPOS_CENTERED,
                                                width,
                                                height,
                                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        return EXIT_FAILURE;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, width, height);

    engine::Particles particles(1000, test_particle, sizeof(test_particle), width, height);

    bool quit = false;
    long last = SDL_GetTicks64();
    int x = width / 2;
    int y = height / 2;
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
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        const long now = SDL_GetTicks64();
        {
            int new_x;
            int new_y;
            SDL_GetMouseState(&new_x, &new_y);
            for (int i = 0; i < 10; ++i) {
                const GLfloat vx = 30.0f * (2.0f * static_cast<GLfloat>(rand()) / RAND_MAX - 1.0f) + 2.0f * (x - new_x); 
                const GLfloat vy = 30.0f * (2.0f * static_cast<GLfloat>(rand()) / RAND_MAX - 1.0f) - 2.0f * (y - new_y); 
                particles.add_particle(1.0f, new_x, height - new_y, vx, vy);
            }
            x = new_x;
            y = new_y;
        }
        particles.update(static_cast<float>(now - last) / 1000.0f);
        last = now;
        particles.draw();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
