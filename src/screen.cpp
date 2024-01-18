#include "screen.h"

#include <glm/gtx/transform.hpp>

#include <SDL.h>

namespace game {

Screen::Screen(float screen_width, float screen_height)
  : destination(screen_width, screen_height),
    time(0.0f),
    shake(0.0f),
    position(0.0f, 0.0f),
    color(0.0f, 0.0f, 0.0f),
    window_x(0),
    window_y(0),
    window_width(screen_width),
    window_height(screen_height)
{
    destination.set_exposure(3.2f);
    destination.set_gamma(0.6f);
}

void Screen::shaking() {
    shake = 0.1f;
}

void Screen::colorize(glm::vec3 color) {
    this->color += color;
}

void Screen::switch_fullscreen(int display_id, bool fullscreen) {
    if (fullscreen) {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(display_id, &mode);
        const float game_aspect_ratio = static_cast<float>(destination.get_screen_width()) / destination.get_screen_height();
        const float display_aspect_ratio = static_cast<float>(mode.w) / mode.h;
        if (display_aspect_ratio > game_aspect_ratio) {
            window_height = mode.h;
            window_width = window_height * game_aspect_ratio;
            window_x = (mode.w - window_width) / 2;
            window_y = 0;
        } else if (display_aspect_ratio < game_aspect_ratio) {
            window_width = mode.w;
            window_height = window_width / game_aspect_ratio;
            window_x = 0;
            window_y = (mode.h - window_height) / 2;
        } else {
            window_width = mode.w;
            window_width = mode.h;
        }
    } else {
        window_width = destination.get_screen_width();
        window_height = destination.get_screen_height();
        window_x = 0;
        window_y = 0;
    }
}

engine::Framebuffer::Binding Screen::bind_as_target() {
    return destination.bind_as_target();
}

void Screen::update(float msec) {
    time += msec;
    if (shake > 0.001f) {
        shake *= 0.9;
    } else {
        shake = 0.0f;
    }
    position = glm::vec2(shake * std::sin(2.0f * M_PI * time / 100.0f),
                         shake * std::cos(2.0f * M_PI * time / 100.0f));
    if (std::abs(color.x) < 0.001f && std::abs(color.y) < 0.001f && std::abs(color.z) < 0.001) {
        color = glm::vec3(0.0f, 0.0f, 0.0f);
    } else {
        color *= 0.9;
    }
}

void Screen::draw() {
    glViewport(window_x, window_y, window_width, window_height);
    destination.draw(glm::translate(glm::vec3(position, 0.0f)), color);
    //destination.draw(glm::translate(glm::vec3(position, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f));
    //destination.draw(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

}
