#pragma once

#include <destination.h>

namespace game {

class Screen {
public:
    Screen(float screen_width, float screen_height);

    void shaking();
    void colorize(glm::vec3 color);

    engine::Framebuffer::Binding bind_as_target();

    void update(float msec);
    void draw();
private:
    engine::Destination destination;
    float time;

    float shake;
    glm::vec2 position;
    glm::vec3 color;
};

}
