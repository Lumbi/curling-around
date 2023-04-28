#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <memory>

class Model;

class ModelLoader
{
    public:
        std::unique_ptr<Model> load(const char * file);
};

#endif
