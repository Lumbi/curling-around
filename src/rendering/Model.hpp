#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <memory>
#include <string>

#include "language/Index.hpp"
#include "math/Matrix.hpp"

class Mesh;

class Model
{
    public:
        struct Node
        {
            std::string name;
            std::vector<Index> meshes;
            Matrix4f transform = Matrix4f::identity();
            Node *parent = nullptr;
            std::vector<std::unique_ptr<Node>> children;

            Matrix4f getModelMatrix() const;
        };

    public:
        Node * getRoot() const;
        void setRoot(std::unique_ptr<Node>);
        void addMesh(std::unique_ptr<Mesh>);
        const std::vector<std::unique_ptr<Mesh>>& getMeshes() const;
        Mesh * getMeshAt(Index) const;

    private:
        std::unique_ptr<Node> root;
        std::vector<std::unique_ptr<Mesh>> meshes;
};

#endif
