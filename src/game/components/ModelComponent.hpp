#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "game/Component.hpp"
#include "rendering/ModelRenderer.hpp"

#include <memory>

class Model;
class Material;

class ModelComponent: public Component
{
    public:
        ModelComponent(Model *, Material *);
        virtual ~ModelComponent();

    public:
        virtual void update() override;
        virtual void draw(Scene &) override;

    private:
        Model *model;
        Material *material; // NOTE: Material should be tied to a mesh instead
        ModelRenderer renderer;
};

#endif
