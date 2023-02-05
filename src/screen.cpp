#include "screen.h"

#include <glm/gtx/transform.hpp>

#include <SDL2/SDL_stdinc.h>

namespace game {

Screen::Screen(float screen_width, float screen_height)
  : destination(screen_width, screen_height),
    time(0.0f),
    shake(0.0f),
    position(0.0f, 0.0f),
    color(0.0f, 0.0f, 0.0f)
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
    destination.draw(glm::translate(glm::vec3(position, 0.0f)), color);
    //destination.draw(glm::translate(glm::vec3(position, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f));
    //destination.draw(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

}
