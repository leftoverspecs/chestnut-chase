#pragma once

#include <glm/vec2.hpp>

#include <controller.h>
#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Player {
public:
    Player(engine::Controller &controller, float x, float y, GLfloat width, GLfloat height);

    glm::vec2 get_position() const { return position; }

    void update(float msec);
    void draw();
private:
    float time;
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    engine::Controller *controller;
    int sprite_index_i;
    int sprite_index_j;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 jump_velocity;
    float last_time_standing;
    float slash_time;
    float screen_width;
};

}
