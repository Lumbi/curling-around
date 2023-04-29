#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <memory>

#include "math/Transform.hpp"

class Mesh;

class Model
{
    public:
        void addMesh(std::unique_ptr<Mesh>);

        const std::vector<std::unique_ptr<Mesh>>& getMeshes() const;

    private:
        std::vector<std::unique_ptr<Mesh>> meshes;
};

#endif
