#pragma once

#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Leaves {
public:
    Leaves(float width, float height);

    void draw();
private:
    float width;
    float height;
    engine::SpriteMap leaves_map;
    engine::SpriteRenderer leaves_renderer;
};

}
