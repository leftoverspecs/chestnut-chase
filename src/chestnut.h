#pragma once

#include <box.h>
#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Chestnut {
public:
    enum class State {
        HANGING,
        FALLING_CLOSED_PLAYER1,
        FALLING_CLOSED_PLAYER2,
        FALLING_OPEN_PLAYER1,
        FALLING_OPEN_PLAYER2,
        HARVESTED,
        GROWING
    };

    Chestnut(float x, float growth_rate, float max_length, float screen_width, float screen_height);

    Chestnut(const Chestnut &) = delete;
    Chestnut(Chestnut &&) = delete;
    Chestnut &operator =(const Chestnut &) = delete;
    Chestnut &operator =(Chestnut &&) = delete;

    void update(float msec);
    void draw();

    void hit(bool female, const engine::Box &sword, glm::vec2 player_velocity);
    bool hits(const engine::Box &body) const;

private:
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    float screen_height;
    float screen_width;
    float growth_rate;
    float max_length;
    float time;

    State state;
    glm::vec2 position;
    glm::vec2 velocity;
    engine::Box fruit;
    engine::Box stem;

    bool capsule_fly;
    glm::vec2 capsule1;
    glm::vec2 capsule2;
    glm::vec2 capsule_velocity;

    float health;
    float hit_cooldown;
};

}
