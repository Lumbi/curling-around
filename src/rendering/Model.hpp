#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <memory>
#include <string>

#include "math/Index.hpp"
#include "math/Matrix.hpp"

class Mesh;

/// @brief A hierarchical structure of multiple meshes.
class Model
{
    public:
        /// @brief A node pointing to a mesh forming a tree structure.
        struct Node
        {
            /// @brief The node's name (mostly for debugging purposes).
            std::string name;

            /// @brief The indices pointing to the meshes at this node.
            std::vector<Index> meshes;

            /// @brief The local transformation matrix at this node.
            Matrix4f transform = Matrix4f::identity();

            /// @brief The parent node.
            Node *parent = nullptr;

            /// @brief The child nodes.
            std::vector<std::unique_ptr<Node>> children;

            /// @brief Get the node's transform relative to the model.
            /// @return
            Matrix4f getModelMatrix() const;
        };

    public:
        /// @brief Get the root node of the model.
        Node * getRoot() const;

        /// @brief Set the root node of the model.
        void setRoot(std::unique_ptr<Node>);

        /// @brief Add a mesh to the model.
        void addMesh(std::unique_ptr<Mesh>);

        /// @brief Get meshes of the model.
        const std::vector<std::unique_ptr<Mesh>>& getMeshes() const;

        /// @brief Get the mesh at the specified index.
        Mesh * getMeshAt(Index) const;

    private:
        std::unique_ptr<Node> root;
        std::vector<std::unique_ptr<Mesh>> meshes;
};

#endif
