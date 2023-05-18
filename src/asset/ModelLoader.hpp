#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <memory>

class Model;

/// @brief A class to load a model from file.
class ModelLoader
{
    public:
        /// @brief Load a model.
        /// @param file The path to the model's file.
        /// @return
        std::unique_ptr<Model> load(const char * file);
};

#endif
