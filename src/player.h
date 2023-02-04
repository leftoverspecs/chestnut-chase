#pragma once

#include <glm/vec2.hpp>

#include <controller.h>
#include <particles.h>
#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Player {
public:
    Player(engine::Controller &controller, bool female, float x, float y, GLfloat width, GLfloat height);

    glm::vec2 get_position() const { return position; }

    void update(float msec);
    void draw();
private:
    bool female;
    float time;
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    engine::Particles dust_particles;
    engine::Controller *controller;
    int sprite_index_i;
    int sprite_index_j;
    bool face_left;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 jump_velocity;
    float last_time_standing;
    float slash_time;
    float screen_width;
};

}
