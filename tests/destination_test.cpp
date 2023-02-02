#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <controller.h>
#include <destination.h>
#include <font.h>

#include <glm/gtx/transform.hpp>

#include <iostream>
#include <string>

#include <font.png.h>

#ifdef _WIN32
extern "C" {

    _declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;

}
#endif

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, width, height);

    engine::Font font(width, height, test_font, sizeof(test_font));
    engine::Destination destination(width, height);
    engine::Controller controller(0);

    bool quit = false;
    long last = SDL_GetTicks64();
    float amplitude = 0.0f;
    float red = 0.0f;
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
                case SDLK_SPACE:
                    amplitude += 0.1f;
                    red += 0.1f;
                    break;
                }
                break;
            }
        }
        if (controller.is_button_a_pressed() > 0) {
            amplitude += 0.1f;
            red += 0.1f;
            controller.rumble(0xFFFF * 3 / 4, 0, 100);
        }
        if (std::abs(controller.get_right_trigger()) > 100) {
            const float amount = std::max(controller.get_right_trigger() / 100000.0f, 0.1f);
            amplitude += amount;
            red += amount;
            controller.rumble(0xFFFF * amount, 0, 100);
        }
        {
            auto binding = destination.bind_as_target();
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            font.clear();
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(10.0f, (height - font.get_height()) / 2.0f, 0.0f));
            model = glm::scale(model, glm::vec3(font.get_width(), font.get_height(), 1.0f));
            font.write(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), "Hello World");
            font.draw();
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        const long t = SDL_GetTicks64();

        float x = 0.0f;
        float y = 0.0f;
        if (amplitude > 0.0001f) {
            x = amplitude * std::sin(2.0f * M_PI * t / 100.0f);
            y = amplitude * std::cos(2.0f * M_PI * t / 100.0f);
            amplitude /= 1.1f;
        } else {
            amplitude = 0.0f;
        }
        if (red > 0.0001f) {
            red /= 1.1f;
        } else {
            red = 0.0f;
        }
        destination.draw(glm::translate(glm::vec3(x, y, 0.0f)), glm::vec3(10.0f * red, 0.0f, 0.0f));
        SDL_GL_SwapWindow(window);

        const long next = SDL_GetTicks64();
        if (next > last) {
            const float fps = 1000.0f / (next - last);
            SDL_SetWindowTitle(window, std::to_string(fps).c_str());
            last = next;
        }
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
