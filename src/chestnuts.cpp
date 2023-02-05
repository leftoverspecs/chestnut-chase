#include "chestnuts.h"

namespace game {

Chestnuts::Chestnuts(Score &score, float screen_width, float screen_height)
  : score(&score),
    screen_width(screen_width),
    screen_height(screen_height),
    cooldown(0.0f)
{ }

void Chestnuts::update(float msec) {
    cooldown -= msec;
    if (cooldown < 0.0f) {
        container.emplace_back(new Chestnut(*score,
                                            (screen_width - 50.0f) * static_cast<float>(rand()) / RAND_MAX + 25.0f,
                                            0.1f * static_cast<float>(rand()) / RAND_MAX + 0.05f,
                                            200.0f * static_cast<float>(rand()) / RAND_MAX + 150.0f,
                                            screen_width, screen_height));
        cooldown = 2000.0f * static_cast<float>(rand()) / RAND_MAX + 3000.0f;
    }
    for (auto &item : container) {
        if (item) {
            if (!item->is_inactive()) {
                item->update(msec);
            } else {
                item.reset();
            }
        }
    }
    container.remove_if([] (const std::unique_ptr<Chestnut> &item) { return !item || item->is_inactive(); });
}

void Chestnuts::draw() {
    for (auto &item : container) {
        if (item) {
            if (!item->is_inactive()) {
                item->draw();
            } else {
                item.reset();
            }
        }
    }
}

void Chestnuts::hit(bool female, const engine::Box &sword, glm::vec2 player_velocity) {
    for (auto &item : container) {
        if (item) {
            if (!item->is_inactive()) {
                item->hit(female, sword, player_velocity);
            } else {
                item.reset();
            }
        }
    }
}

bool Chestnuts::hits(const engine::Box &body) {
    for (auto &item : container) {
        if (item) {
            if (!item->is_inactive()) {
                if (item->hits(body)) {
                    return true;
                }
            } else {
                item.reset();
            }
        }
    }
    return false;
}

}
