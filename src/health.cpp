#include "health.h"

namespace game {

Health::Health(bool female, float screen_width, float screen_height)
  : female(female),
    value(100.0f),
    bar(female ? 25.0f : screen_width - 25.0f, screen_height - 50.0f, female ? 2.0f * value : -2.0f * value, 25.0f, screen_width, screen_height)
{ }

void Health::adjust(float update) {
    value += update;
    bar.resize(female ? 2.0f * value : -2.0f * value, 25.0f);
}
void Health::draw() {
    bar.draw_filled(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

}
