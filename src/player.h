#pragma once

#include <glm/vec2.hpp>

#include <controller.h>
#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Player {
public:
    Player(engine::Controller &controller, float x, float y, GLfloat width, GLfloat height);

    void update(float msec);
    void draw();
private:
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    engine::Controller *controller;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 jump_velocity;
    float last_time_standing;
    float width;
};

}
