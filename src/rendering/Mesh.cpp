#include "Mesh.hpp"

// Positions for vertex attributes

static const GLuint VERTEX_ATTRIB_POSITION = 0;
static const GLuint VERTEX_ATTRIB_NORMAL = 1;
static const GLuint VERTEX_ATTRIB_TEXCOORD0 = 2;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Index> indices)
    : vertices(vertices),
      indices(indices)
{
    // Create the VBOs and VAO

    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    glGenVertexArrays(1, &vertexArray);

    // Put the vertex data into the buffers

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), &indices[0], GL_STATIC_DRAW);

    // Set the vertex attributes

    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(
        VERTEX_ATTRIB_POSITION,
        3, GL_FLOAT, // vec3
        GL_FALSE, // normalize
        sizeof(Vertex), // stride
        (void*) 0 // offset
    );

    glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
    glVertexAttribPointer(
        VERTEX_ATTRIB_NORMAL,
        3, GL_FLOAT, // vec3
        GL_FALSE, // normalize
        sizeof(Vertex), // stride
        (void*) offsetof(Vertex, normal) // offset
    );

    glEnableVertexAttribArray(VERTEX_ATTRIB_TEXCOORD0);
    glVertexAttribPointer(
        VERTEX_ATTRIB_TEXCOORD0,
        2, GL_FLOAT, // vec2
        GL_FALSE, // normalize
        sizeof(Vertex), // stride
        (void*) offsetof(Vertex, texCoord0) // offset
    );

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    // Destroy the VBOs and VAO

    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &elementBuffer);
}
