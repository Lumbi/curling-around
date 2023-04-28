#include "ModelLoader.hpp"

#include "language/Index.hpp"
#include "rendering/Vertex.hpp"
#include "rendering/Mesh.hpp"
#include "rendering/Model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

std::unique_ptr<Model> ModelLoader::load(const char *file)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(file, aiProcess_Triangulate);
    if (!scene) {
        printf("Error: Failed to read model %s\n", importer.GetErrorString());
        return { nullptr };
    }

    auto model = std::make_unique<Model>();

    for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
        aiMesh *meshData = scene->mMeshes[meshIndex];
        std::vector<Vertex> vertices;
        std::vector<Index> indices;
        for (int vertexIndex = 0; vertexIndex < meshData->mNumVertices; vertexIndex++) {
            Vertex vertex;
            aiVector3D positionData = meshData->mVertices[vertexIndex];
            vertex.position = { positionData.x, positionData.y, positionData.z };
            aiVector3D normalData = meshData->mNormals[vertexIndex];
            vertex.normal = { normalData.x, normalData.y, normalData.z };
            vertices.push_back(vertex);
        }

        for (int faceIndex = 0; faceIndex < meshData->mNumFaces; faceIndex++) {
            aiFace face = meshData->mFaces[faceIndex];
            for (int index = 0; index < face.mNumIndices; index++) {
                indices.push_back(face.mIndices[index]);
            }
        }

        if (!vertices.empty() && !indices.empty()) {
            model->addMesh(std::make_unique<Mesh>(vertices, indices));
        } else {
            printf("Error: Mesh in loaded model has no vertices\n");
        }
    }

    return model;
}
