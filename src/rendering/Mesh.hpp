#ifndef MESH_H
#define MESH_H

#include <vector>

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include "rendering/Vertex.hpp"
#include "language/Index.hpp"

static const GLuint VERTEX_ATTRIB_POSITION = 0;
static const GLuint VERTEX_ATTRIB_NORMAL = 1;

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
