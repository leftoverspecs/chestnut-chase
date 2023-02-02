#include "player.h"

#include <player.png.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace game {

namespace {

glm::vec2 GRAVITY(0.0f, -0.005f);

}

Player::Player(engine::Controller &controller, float x, float y, GLfloat width, GLfloat height)
  : sprites(player, sizeof(player), 2, 2),
    renderer(sprites, width, height),
    controller(&controller),
    position(x, y),
    velocity(0.0f, 0.0f),
    jump_velocity(0.0f, 0.0f),
    last_time_standing(0.0f),
    width(width)
{ }

void Player::update(float msec) {
    velocity += GRAVITY * msec;
    int intensity = controller->is_button_a_pressed();
    if (intensity > 0 && last_time_standing < 80.0f) {
        velocity.y += 0.5f;
        last_time_standing += msec;
    }
    intensity = controller->is_button_left_pressed();
    if (intensity > 0) {
        velocity.x -= 0.1f;
    }
    intensity = controller->is_button_right_pressed();
    if (intensity > 0) {
        velocity.x += 0.1f;
    }
    velocity.x /= 1.1f;
    velocity.x = glm::clamp(velocity.x, -10.0f, 10.0f);
    velocity.y = glm::clamp(velocity.y, -10.0f, 10.0f);
    position += velocity * msec;
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.y = 0.0f;
        last_time_standing = 0.0f;
    }
    if (position.x < 0) {
        position.x = 0.0f;
        velocity.x = 0.0f;
    } else if (position.x > width - sprites.get_sprite_width()) {
        position.x = width - sprites.get_sprite_width();
        velocity.x = 0.0f;
    }
}

void Player::draw() {
    renderer.clear();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(sprites.get_sprite_width(), sprites.get_sprite_height(), 1.0f));
    renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
    renderer.draw();
}

}
