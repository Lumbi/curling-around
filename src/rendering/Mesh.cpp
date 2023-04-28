#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Index> indices)
    : vertices(vertices),
      indices(indices)
{
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &elementBuffer);
    glGenVertexArrays(1, &vertexArray);

    glBindVertexArray(vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), &indices[0], GL_STATIC_DRAW);

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

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
    glDeleteBuffers(1, &elementBuffer);
}

void Mesh::draw()
{

}
