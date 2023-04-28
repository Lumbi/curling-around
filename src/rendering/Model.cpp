#include "Model.hpp"

#include "Mesh.hpp"

void Model::addMesh(std::unique_ptr<Mesh> mesh)
{
    meshes.push_back(std::move(mesh));
}

const std::vector<std::unique_ptr<Mesh>>& Model::getMeshes() const
{
    return meshes;
}
