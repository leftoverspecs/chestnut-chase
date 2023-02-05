#pragma once

#include "spritemap.h"
#include "spriterenderer.h"

#include <cstddef>
#include <vector>

namespace engine {

class Particles  {
public:
    Particles(std::size_t num, const unsigned char *sprite, std::size_t size, GLfloat width, GLfloat height);

    void add_particle(GLfloat life, GLfloat x, GLfloat y, GLfloat vx, GLfloat vy);

    void update(GLfloat ticks);
    void draw();

    bool is_empty() const;

private:
    SpriteMap sprite;
    SpriteRenderer renderer;

    struct Particle {
        GLfloat life;
        GLfloat initial_life;
        GLfloat x;
        GLfloat y;
        GLfloat vx;
        GLfloat vy;
    };

    std::vector<Particle> particles;
};

}
