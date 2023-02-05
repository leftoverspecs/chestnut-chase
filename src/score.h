#pragma once

#include <font.h>

namespace game {

class Score {
public:
    Score(engine::Font &font, float screen_width, float screen_height);

    void increase();
    void reset();

    void write();
private:
    engine::Font *font;
    float screen_width;
    float screen_height;
    int value;
};

}
