#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Actor;
class Component;
class Camera;

/// @brief A scene where a hierachy of actors are updated.
class Scene
{
    public:
        /// @brief Initializes the scene with a default empty root actor.
        Scene();

        /// @brief Get the scene's root actor.
        Actor * getRoot();

        /// @brief Get the scene's camera.
        Camera * getCamera();

        /// @brief Set the scene's camera.
        void setCamera(std::unique_ptr<Camera>);

    private:
        std::unique_ptr<Actor> root;
        std::unique_ptr<Camera> camera;
};

#endif
