#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector.hpp"

struct Vertex
{
    Vector3f position;
    Vector3f normal;
    Vector2f texCoord0;
};

#endif
