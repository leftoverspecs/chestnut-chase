#include "player.h"

#include <player2.png.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace game {

namespace {

glm::vec2 GRAVITY(0.0f, -0.0025f);

const float JUMP_STRENGTH = 0.275f;
const float JUMP_COOLDOWN = 100.0f;

const float HORIZONTAL_SPEED = 0.1f;
const float HORIZONTAL_FRICTION = 1.1f;
const float HORIZONTAL_THRESHOLD = 0.01f;

const float MAX_VERTICAL_SPEED = 10.0f;
const float MAX_HORIZONTAL_SPEED = 10.0f;

const float GROUND = 10.0f;
const float GROUND_MARGIN = GROUND + 10.0f;
const float LEFT_BORDER = 25.0f;
const float RIGHT_BORDER = 35.0f;

}

Player::Player(engine::Controller &controller, float x, float y, GLfloat width, GLfloat height)
  : time(0.0f),
    sprites(player2, sizeof(player2), 13, 16),
    renderer(sprites, width, height),
    controller(&controller),
    sprite_index_i(0),
    sprite_index_j(0),
    position(x, y),
    velocity(0.0f, 0.0f),
    jump_velocity(0.0f, 0.0f),
    last_time_standing(0.0f),
    screen_width(width)
{ }

void Player::update(float msec) {
    time += msec;
    velocity += GRAVITY * msec;
    int intensity = controller->is_button_a_pressed();
    if (intensity > 0 && last_time_standing < JUMP_COOLDOWN) {
        velocity.y += JUMP_STRENGTH;
        last_time_standing += msec;
    }
    intensity = controller->is_button_left_pressed();
    if (intensity > 0) {
        velocity.x -= HORIZONTAL_SPEED; // HORIZONTAL_ACCELERATION * msec;
    }
    intensity = controller->is_button_right_pressed();
    if (intensity > 0) {
        velocity.x += HORIZONTAL_SPEED; // HORIZONTAL_ACCELERATION * msec;
    }
    velocity.x /= HORIZONTAL_FRICTION;
    if (std::abs(velocity.x) < HORIZONTAL_THRESHOLD) {
        velocity.x = 0.0f;
    }
    velocity.x = glm::clamp(velocity.x, -MAX_HORIZONTAL_SPEED, MAX_HORIZONTAL_SPEED);
    velocity.y = glm::clamp(velocity.y, -MAX_VERTICAL_SPEED, MAX_VERTICAL_SPEED);
    position += velocity * msec;
    if (position.y < GROUND) {
        position.y = GROUND;
        velocity.y = 0.0f;
        last_time_standing = 0.0f;
    }
    if (position.x < LEFT_BORDER) {
        position.x = LEFT_BORDER;
        velocity.x = 0.0f;
    } else if (position.x > screen_width - 128.0f + RIGHT_BORDER) {
        position.x = screen_width - 128.0f + RIGHT_BORDER;
        velocity.x = 0.0f;
    }

    if (position.y > GROUND_MARGIN) {
        // Player is in air
        sprite_index_j = 5;
        if (velocity.y > 0.0f) {
            // Player ascends
            sprite_index_i = 2;
        } else if (velocity.y < 0.0f) {
            // Player descends
            sprite_index_i = 4;
        } else {
            // Player at peak
            sprite_index_i = 3;
        }
    } else if (position.y < GROUND_MARGIN) {
        // Player is considered on the ground
        if (std::abs(velocity.x) > 0.0f) {
            // Player walks
            sprite_index_i = static_cast<int>(std::floor(time / 100.0f)) % 7;
            sprite_index_j = 1;
        } else {
            // Player is idle
            sprite_index_i = static_cast<int>(std::floor(time / 250.0f)) % 13;
            sprite_index_j = 0;
        }
    }
    //std::cout << sprite_index_i << ", " << sprite_index_j << '\n';
}

void Player::draw() {
    renderer.clear();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(128.0f, 128.0f, 1.0f));
    model = glm::scale(model, glm::vec3(velocity.x > 0.0f ? 1.0f : -1.0f, 1.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
    renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), sprite_index_i, sprite_index_j);
    renderer.draw();
}

}
