#ifndef ACTOR_H
#define ACTOR_H

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "math/Transform.hpp"

#include <memory>
#include <vector>
#include <concepts>

class Component;
class Renderer;

/// @brief An actor in placed in a scene. It contains child actors and components.
class Actor
{
    public:
        /// @brief Initializes an empty actor at the origin.
        Actor();

        /// @brief Destroy the actor.
        virtual ~Actor();

        /// @brief Get the actor's transform.
        Transform & getTransform();

        /// @brief Get the actor's transformation matrix to convert from local space to world space.
        Matrix4f getLocalToWorldMatrix();

        /// @brief Get the position of the actor in world space.
        Vector3f getWorldPosition();

        /// @brief Update the actor for a single frame. Also update the child actors and components.
        virtual void update();

        /// @brief Draw the actor using the provided renderer.
        virtual void draw(Renderer &);

        /// @brief Get the components attached to the actor.
        const std::vector<std::unique_ptr<Component>>& getComponents() const;

        /// @brief Attach a component to the actor.
        void attachComponent(std::unique_ptr<Component>);

        /// @brief Detach a component from the actor. The address is used to identify the component.
        void detachComponent(Component *);

        /// @brief Get the first component matching a specified type.
        /// @tparam T A class derived from Component
        /// @return The component matching the type or nullptr if none found.
        template<std::derived_from<Component> T>
        T * getComponent() {
            for (auto&& component : components) {
                T * found = dynamic_cast<T*>(component.get());
                if (found) { return found; }
            }
            return nullptr;
        }

        /// @brief Get the child actors of this actor.
        const std::vector<std::unique_ptr<Actor>>& getChildren() const;

        /// @brief Add a child actor.
        void addChild(std::unique_ptr<Actor>);

        /// @brief Remove a child actor.
        void removeChild(Actor *);

        /// @brief Remove this actor from its parent.
        void removeFromParent();

    private:
        Transform transform;
        Actor *parent;
        std::vector<std::unique_ptr<Actor>> children;
        std::vector<Actor *> childrenToRemove;
        std::vector<std::unique_ptr<Component>> components;
        std::vector<Component *> componentsToRemove;
};

#endif
