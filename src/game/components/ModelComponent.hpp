#ifndef MODEL_COMPONENT_H
#define MODEL_COMPONENT_H

#include "game/Component.hpp"

#include <memory>

class Model;
class Material;

/// @brief A component that handles rendering a model attached to an actor.
class ModelComponent: public Component
{
    public:
        /// @brief Initialize the model component.
        /// @param model The model to render.
        /// @param material The material to apply to the model during rendering.
        ModelComponent(Model *model, Material *material);

        /// @brief Destroy the model component.
        virtual ~ModelComponent();

    public:
        /// @brief Update the model component for a single frame.
        virtual void update() override;

        /// @brief Draw the model component using the provided renderer.
        ///        The model is drawn relative to the actor's transform.
        virtual void draw(Renderer &) override;

    private:
        Model *model;
        Material *material; // NOTE: Material should be tied to a mesh instead
};

#endif
