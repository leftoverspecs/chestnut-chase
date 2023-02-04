#include "leaves.h"

#include <leaves.png.h>
#include <treelayer1.png.h>
#include <treelayer2.png.h>
#include <treelayer3.png.h>

#include <glm/gtc/matrix_transform.hpp>

namespace game {

Leaves::Leaves(float width, float height)
  : width(width),
    height(height),
    leaves_map(leaves, sizeof(leaves), 1, 1),
    leaves_renderer(leaves_map, width, height)
{ }

void Leaves::draw() {
    leaves_renderer.clear();

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));
    leaves_renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, 0);
    leaves_renderer.draw();
}

}
