#include "particles.h"

#include <stdexcept>

#include <glm/gtx/transform.hpp>

namespace engine {

Particles::Particles(std::size_t num, const unsigned char *sprite, std::size_t size, GLfloat width, GLfloat height)
  : sprite(sprite, size, 1, 1),
    renderer(this->sprite, width, height),
    particles(num, Particle{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f })
{ }

void Particles::add_particle(GLfloat life, GLfloat x, GLfloat y, GLfloat vx, GLfloat vy) {
    for (auto &p : particles) {
        if (p.life <= 0.0f) {
            p.life = life;
            p.initial_life = life;
            p.x = x;
            p.y = y;
            p.vx = vx;
            p.vy = vy;
            return;
        }
    }
    throw std::runtime_error("Too many particles");
}

void Particles::update(GLfloat ticks) {
    renderer.clear();
    for (auto &p : particles) {
        if (p.life > 0.0f) {
            p.x += ticks * p.vx;
            p.y += ticks * p.vy;
            p.life -= ticks;
            if (p.life > 0.0f) {
                glm::mat4 model(1.0f);
                model = glm::translate(model, glm::vec3(p.x, p.y, 0.0f));
                model = glm::scale(model, glm::vec3(2.0f * sprite.get_sprite_width(), 2.0f * sprite.get_sprite_height(), 1.0));
                renderer.queue(model, glm::vec4(1.0f, 1.0f, 1.0f, p.life / p.initial_life), 0, 0);
            }
        }
    }
}

void Particles::draw() {
    renderer.draw();
}

bool Particles::is_empty() const {
    for (auto &p : particles) {
        if (p.life > 0.0f) {
            return false;
        }
    }
    return true;
}

}
