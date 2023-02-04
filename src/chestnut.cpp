#include "chestnut.h"

#include <glm/gtc/matrix_transform.hpp>

#include <chestnut.png.h>

namespace game {

Chestnut::Chestnut(float x, float growth, float max_length, float width, float height)
  : sprites(chestnut, sizeof(chestnut), 3, 1),
    renderer(sprites, width, height),
    time(0.0f),
    height(height),
    x(x),
    growth(growth),
    max_length(max_length),
    length(0),
    dropping(false)
{ }

void Chestnut::update(float msec) {
    if (!dropping) {
        time += msec;
        length = max_length * growth * time / (growth * time + max_length);
    } else {
        velocity.y += -0.001f * msec;
        position += msec * velocity;
    }
}

void Chestnut::draw() {
    renderer.clear();

    if (!dropping) {
        const int num = static_cast<int>(length / 32.0f);
        for (int i = 0; i < num; ++i) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(x, height - length + 16.0 + i * 64.0, 0.0f));
            model = glm::scale(model, glm::vec3(32.0f, 64.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
            renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 0);
        }

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(x, height - length, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
    } else {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
    }

    renderer.draw();
}

void Chestnut::drop(float vx) {
    dropping = true;
    position = glm::vec2(x, height - length);
    velocity = glm::vec2(vx, 0);
}

}
