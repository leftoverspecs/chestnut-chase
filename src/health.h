#pragma once

#include <box.h>
#include <spritemap.h>
#include <spriterenderer.h>

namespace game {

class Health {
public:
    Health(bool female, float screen_width, float screen_height);

    Health(const Health &);
    Health(Health &&);
    Health &operator = (const Health &);
    Health &operator = (Health &&);

    void adjust(float update);
    void draw();

    int get_value() const { return value; }

private:
    engine::SpriteMap sprites;
    engine::SpriteRenderer renderer;
    float screen_width;
    float screen_height;
    bool female;
    float value;
    engine::Box bar;
    engine::Box background;
};

}
