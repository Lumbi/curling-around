#ifndef COMPONENT_H
#define COMPONENT_H

class Actor;
class Scene;

/// @brief An abstract component that can be derived to encapsulate game logic.
class Component
{
    public:
        /// @brief Initialize and empty component without an actor.
        Component();

        /// @brief Destroy the component.
        virtual ~Component();

        /// @brief Update the component for a single frame.
        virtual void update() = 0;

        /// @brief Draw the component in a scene.
        virtual void draw(Scene &) = 0;

        /// @brief Get the component's parent actor.
        Actor * getActor() const;

        /// @brief Set the component's parent actor.
        void setActor(Actor *);

    private:
        Actor *actor;
};

#endif
