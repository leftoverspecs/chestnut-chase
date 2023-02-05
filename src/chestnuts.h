#pragma once

#include "chestnut.h"

#include <box.h>

#include <memory>
#include <list>

namespace game {

class Score;

class Chestnuts {
public:
    Chestnuts(Score &score, float screen_width, float screen_height);

    void update(float msec);
    void draw();

    void hit(bool female, const engine::Box &sword, glm::vec2 player_velocity);
    bool hits(const engine::Box &body);

private:
    Score *score;
    float screen_width;
    float screen_height;
    float time;
    float cooldown;

    std::list<std::unique_ptr<Chestnut>> container;
};

}
