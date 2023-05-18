#ifndef VERTEX_H
#define VERTEX_H

#include "math/Vector.hpp"

/// @brief A point in 3D space with additional attributes.
struct Vertex
{
    /// @brief The world-space position of the vertex.
    Vector3f position;

    /// @brief The surface normal at the vertex.
    Vector3f normal;

    /// @brief The UV coordinate for texture index 0 at this vertex.
    Vector2f texCoord0;
};

#endif
