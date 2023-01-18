#pragma once

#include "buffer.h"
#include "vertexarray.h"

namespace engine {

class Quad {
public:
    static const int ATTRIBUTE_POSITION;
    static const int ATTRIBUTE_TEXTURE_COORD;

    Quad();

    void draw() const;
private:
    VertexArray vao;
    Buffer vertices;
};

}
