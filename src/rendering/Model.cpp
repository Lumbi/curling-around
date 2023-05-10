#include "Model.hpp"

#include "Mesh.hpp"

Model::Node * Model::getRoot() const
{
    return root.get();
}

void Model::setRoot(std::unique_ptr<Model::Node> node)
{
    root = std::move(node);
}

void Model::addMesh(std::unique_ptr<Mesh> mesh)
{
    meshes.push_back(std::move(mesh));
}

const std::vector<std::unique_ptr<Mesh>>& Model::getMeshes() const
{
    return meshes;
}

Mesh * Model::getMeshAt(Index i) const
{
    return meshes[i].get();
}

Matrix4f Model::Node::getModelTransform() const
{
    Matrix4f worldTransform = transform;
    Model::Node *nextParent = parent;
    while (nextParent) {
        worldTransform = worldTransform * nextParent->transform;
        nextParent = nextParent->parent;
    }
    return worldTransform;
}
