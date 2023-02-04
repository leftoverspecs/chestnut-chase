#include "background.h"

#include <leaves.png.h>
#include <treelayer1.png.h>
#include <treelayer2.png.h>
#include <treelayer3.png.h>

#include <glm/gtc/matrix_transform.hpp>

namespace game {

Background::Background(float width, float height)
  : width(width),
    height(height),
    layer1(treelayer1, sizeof(treelayer1), 1, 1),
    layer2(treelayer2, sizeof(treelayer2), 1, 1),
    layer3(treelayer3, sizeof(treelayer3), 1, 1),
    renderer1(layer1, width, height),
    renderer2(layer2, width, height),
    renderer3(layer3, width, height),
    delta(0.0f)
{ }

void Background::update(float x) {
    delta = x - width;
}

void Background::draw() {
    renderer1.clear();
    renderer2.clear();
    renderer3.clear();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    renderer1.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((1.25f - 1.0f) * delta, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(width * 1.25f, height, 1.0f));
    renderer2.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3((1.5f - 1.0f) * delta, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(width * 1.5f, height, 1.0f));
    renderer3.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);

    renderer3.draw();
    renderer2.draw();
    renderer1.draw();
}

}
