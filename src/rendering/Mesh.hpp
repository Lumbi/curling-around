#ifndef MESH_H
#define MESH_H

#include <vector>

#include "rendering/Vertex.hpp"
#include "math/Index.hpp"

#include "OpenGL.h"

/// @brief Contains vertex data. A model is composed of multiple meshes.
/// @see Model
class Mesh
{
    friend class ModelRenderer;

    public:
        /// @brief The vertices of this mesh.
        std::vector<Vertex> vertices;

        /// @brief The indices defining the order of vertices of this mesh.
        std::vector<Index> indices;

        /// @brief Initialize the mesh.
        /// @param vertices The vertices.
        /// @param indices The indices.
        Mesh(std::vector<Vertex> vertices, std::vector<Index> indices);

        // Disable the copy-constructor and copy-assignment operator.
        Mesh(Mesh&) = delete;
        Mesh& operator=(Mesh&) = delete;

        /// @brief Destroy the mesh.
        ~Mesh();

    private:
        GLuint vertexBuffer;
        GLuint vertexArray;
        GLuint elementBuffer;
};

#endif
