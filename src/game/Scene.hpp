#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Actor;
class Renderer;

/// @brief A scene where a hierachy of actors are updated.
class Scene
{
    public:
        /// @brief Initializes the scene with a default empty root actor.
        Scene();

        /// @brief Get the scene's root actor.
        Actor * getRoot();

        void update();

        void draw(Renderer &);

    private:
        std::unique_ptr<Actor> root;
};

#endif
