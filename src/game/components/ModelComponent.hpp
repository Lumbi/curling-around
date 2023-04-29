#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "game/Component.hpp"
#include "rendering/ModelRenderer.hpp"

#include <memory>

class Model;

class ModelComponent: public Component
{
    public:
        ModelComponent(Model *);
        virtual ~ModelComponent();

    public:
        virtual void update() override;
        virtual void draw() override;

    private:
        Model *model;
        ModelRenderer renderer;
};

#endif
