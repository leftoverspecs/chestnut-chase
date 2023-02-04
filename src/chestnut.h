#pragma once

#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Chestnut {
public:
    Chestnut(float x, float growth, float max_length, float width, float height);

    Chestnut(const Chestnut &) = delete;
    Chestnut(Chestnut &&) = delete;
    Chestnut &operator =(const Chestnut &) = delete;
    Chestnut &operator =(Chestnut &&) = delete;

    void update(float msec);
    void draw();

    void drop(float vx);

    glm::vec2 get_position() const {
        return glm::vec2(x, height - length);
    }

private:
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    float time;
    float height;
    float x;
    float growth;
    float max_length;
    float length;
    float dropping;
    glm::vec2 position;
    glm::vec2 velocity;
};

}
