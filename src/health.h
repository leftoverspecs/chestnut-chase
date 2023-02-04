#pragma once

#include <box.h>

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

private:
    bool female;
    float value;
    engine::Box bar;
};

}
