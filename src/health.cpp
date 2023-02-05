#include "health.h"

#include <player.png.h>
#include <player2.png.h>

#include <glm/gtc/matrix_transform.hpp>

namespace game {

Health::Health(bool female, float screen_width, float screen_height)
  : sprites(female ? player : player2, female ? sizeof(player) : sizeof(player2), female ? 9 : 13, female ? 7 : 16),
    renderer(sprites, screen_width, screen_height),
    screen_width(screen_width),
    screen_height(screen_height),
    female(female),
    value(100.0f),
    bar(female ? 50.0f : screen_width - 50.0f, screen_height - 50.0f, female ? 2.0f * value : -2.0f * value, 25.0f, screen_width, screen_height),
    background(female ? 10.0f : screen_width - 10.0, screen_height - 60.0f, female ? 250.0f : -250.0f, 45.0f, screen_width, screen_height)
{ }

void Health::adjust(float update) {
    value += update;
    bar.resize(female ? 2.0f * value : -2.0f * value, 25.0f);
}
void Health::draw() {
    background.draw_filled(glm::vec4(1.0f, 1.0f, 1.0f, 0.25f));

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(female ? 30.0f : screen_width - 30.0f, screen_height - 55.0f, 0.0f));
    model = glm::scale(model, glm::vec3(50.0f, 50.0f, 1.0f));
    model = glm::scale(model, glm::vec3(female ? 1.0f : -1.0f, 1.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-14.0f / 32.0f, 0.0f, 0.0f));
    renderer.clear();
    renderer.queue(model, glm::vec4(2.0f, 2.0f, 2.0f, 1.0), 0, 0);
    renderer.draw();

    bar.draw_filled(female ? glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) : glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

}
