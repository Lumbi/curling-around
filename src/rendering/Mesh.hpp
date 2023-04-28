#ifndef MESH_H
#define MESH_H

#include <vector>

#include "rendering/Vertex.hpp"
#include "language/Index.hpp"

#include "OpenGL.h"

static const GLuint VERTEX_ATTRIB_POSITION = 0;
static const GLuint VERTEX_ATTRIB_NORMAL = 1;
static const GLuint VERTEX_ATTRIB_TEXCOORD0 = 2;

class Mesh
{
    friend class ModelRenderer;

    public:
        std::vector<Vertex> vertices;
        std::vector<Index> indices;

        Mesh(std::vector<Vertex> vertices, std::vector<Index> indices);

        Mesh(Mesh&) = delete;
        Mesh& operator=(Mesh&) = delete;

        ~Mesh();

        void draw();

    private:
        GLuint vertexBuffer;
        GLuint vertexArray;
        GLuint elementBuffer;
};

#endif
