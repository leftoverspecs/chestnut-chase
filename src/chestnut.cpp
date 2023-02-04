#include "chestnut.h"

#include <glm/gtc/matrix_transform.hpp>

#include <chestnut.png.h>

namespace game {

Chestnut::Chestnut(float x, float growth_rate, float max_length, float screen_width, float screen_height)
  : sprites(chestnut, sizeof(chestnut), 7, 1),
    renderer(sprites, screen_width, screen_height),
    screen_height(screen_height),
    screen_width(screen_width),
    growth_rate(growth_rate),
    max_length(max_length),
    time(0.0f),
    state(State::HANGING),
    position(x, screen_height),
    velocity(0.0f, 0.0f),
    fruit(position.x, position.y, 64.0f, 64.0f, screen_width, screen_height),
    stem(0.0f, 0.0f, 20.0f, 32.0f, screen_width, screen_height),
    capsule_fly(false),
    capsule1(0.0f, 0.0f),
    capsule2(0.0f, 0.0f),
    capsule_velocity(0.0f, 0.0f),
    health(50.0f),
    hit_cooldown(0.0f)
{ }

void Chestnut::update(float msec) {
    if (health <= 0.0f) {
        return;
    }

    switch (state) {
    case State::HANGING:
        time += msec;
        position.y = screen_height - max_length * growth_rate * time / (growth_rate * time + max_length);
        break;
    case State::FALLING_CLOSED_PLAYER1:
    case State::FALLING_CLOSED_PLAYER2:
    case State::FALLING_OPEN_PLAYER1:
    case State::FALLING_OPEN_PLAYER2:
        velocity.y += -0.001f * msec;
        position += msec * velocity;
        if (position.y < 25.0f) {
            state = State::GROWING;
            time = 0.0f;
            position.y = 25.0f;
            velocity = glm::vec2(0.0f, 0.0f);
        }
        if (position.x < 25.0f || position.x > screen_width - 45.0f) {
            velocity.x = -velocity.x;
        }
        break;
    case State::GROWING:
        time += msec;
        position.y = 25.0f + max_length * growth_rate * time / (growth_rate * time + max_length);
        if (hit_cooldown > 0.0f) {
            hit_cooldown -= msec;
        } else {
            hit_cooldown = 0.0f;
        }
        break;
    }
    if (capsule_fly) {
        capsule_velocity.y += -0.001 * msec;
        capsule1 += msec * glm::vec2(-capsule_velocity.x, capsule_velocity.y);
        capsule2 += msec * glm::vec2(capsule_velocity.x, capsule_velocity.y);
        if (capsule1.y < -25.0f) {
            capsule1.y = -25.0f;
            capsule2.y = -25.0f;
            capsule_velocity = glm::vec2(0.0f, 0.0f);
        }
    }
    fruit.relocate(position.x - 32.0f, position.y - 32.0f);
    if (state == State::HANGING) {
        stem.relocate(position.x - 10.0f, position.y + 32.0f);
        stem.resize(20.0f, screen_height - position.y);
    } else if (state == State::GROWING) {
        stem.relocate(position.x - 10.0f, 0.0f);
        stem.resize(20.0f, position.y);
    }
}

void Chestnut::draw() {
    if (health < 0.0f) {
        return;
    }
    renderer.clear();

    if (state == State::HANGING) {
        const int num = static_cast<int>(screen_height - position.y / 32.0f);
        for (int i = 0; i < num; ++i) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(position.x, position.y + 16.0 + i * 64.0, 0.0f));
            model = glm::scale(model, glm::vec3(32.0f, 64.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
            renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 0);
        }
    }

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
    if (state == State::HANGING || state == State::FALLING_CLOSED_PLAYER1 || state == State::FALLING_CLOSED_PLAYER2) {
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
    } else if (state == State::FALLING_OPEN_PLAYER1 || state == State::FALLING_OPEN_PLAYER2) {
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 0);
    } else if (state == State::GROWING) {
        float alpha = 1.0f;
        if (hit_cooldown > 0.0f) {
            alpha = static_cast<int>(std::floor(hit_cooldown / 5.0f)) % 2;
        }

        const int num = static_cast<int>((25.0f + position.y) / 32.0f) - 2;
        for (int i = 0; i < num; ++i) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(position.x, position.y - 48.0f - i * 64.0, 0.0f));
            model = glm::scale(model, glm::vec3(32.0f, 64.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
            renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, alpha), 2, 0);
        }

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position.x, 25.0f, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, alpha), 5, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, alpha), 6, 0);
    }

    if (capsule_fly) {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(capsule1, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 3, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(capsule2, 0.0f));
        model = glm::scale(model, glm::vec3(64.0f, 64.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
        renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 4, 0);
    }

    renderer.draw();
    fruit.draw(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    stem.draw(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void Chestnut::hit(bool female, const engine::Box &sword, glm::vec2 player_velocity) {
    switch (state) {
    case State::HANGING:
        if (sword.collides_with_box(stem)) {
            state = female ? State::FALLING_CLOSED_PLAYER1 : State::FALLING_CLOSED_PLAYER2;
            velocity = glm::vec2(0.1f * player_velocity.x, 0);
        }
        break;
    case State::FALLING_CLOSED_PLAYER1:
    case State::FALLING_OPEN_PLAYER1:
        if (!female) {
            if (sword.collides_with_box(fruit)) {
                state = State::FALLING_OPEN_PLAYER2;
                if (!capsule_fly) {
                    capsule_fly = true;
                    capsule1 = position;
                    capsule2 = position;
                    capsule_velocity = glm::vec2(0.25f, 0.0f);
                }
                velocity = glm::vec2(0.2f * player_velocity.x, 1.1f * std::abs(velocity.y));
            }
        }
        break;
    case State::FALLING_CLOSED_PLAYER2:
    case State::FALLING_OPEN_PLAYER2:
        if (female) {
            if (sword.collides_with_box(fruit)) {
                state = State::FALLING_OPEN_PLAYER1;
                if (!capsule_fly) {
                    capsule_fly = true;
                    capsule1 = position;
                    capsule2 = position;
                    capsule_velocity = glm::vec2(0.25f, 0.0f);
                }
                velocity = glm::vec2(0.2f * player_velocity.x, 1.1f * std::abs(velocity.y));
            }
        }
        break;
    case State::GROWING:
        if (sword.collides_with_box(stem)) {
            health -= 1.0f;
            hit_cooldown = 1000.0f;
        }
    }
}

bool Chestnut::hits(const engine::Box &body) const {
    return health > 0.0f && state == State::GROWING && body.collides_with_box(stem);
}

}
