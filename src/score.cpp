#include "score.h"

#include <glm/gtc/matrix_transform.hpp>

namespace game {

Score::Score(engine::Font &font, float screen_width, float screen_height)
  : font(&font), screen_width(screen_width), screen_height(screen_height), value(0)
{ }

void Score::increase() {
    ++value;
}

void Score::reset() {
    value = 0;
}

void Score::write() {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(screen_width / 2.0f - 20.0f, screen_height - 60.0f, 0.0f));
    model = glm::scale(model, glm::vec3(font->get_width(), font->get_height(), 1.0f));
    font->write(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), std::to_string(value).c_str());
}

}
