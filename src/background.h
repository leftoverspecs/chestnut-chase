#pragma once

#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Background {
public:
    Background(float width, float height);

    void update(float x);
    void draw();
private:
    float width;
    float height;
    engine::SpriteMap layer1;
    engine::SpriteMap layer2;
    engine::SpriteMap layer3;
    engine::SpriteRenderer renderer1;
    engine::SpriteRenderer renderer2;
    engine::SpriteRenderer renderer3;
    float delta;
};

}
