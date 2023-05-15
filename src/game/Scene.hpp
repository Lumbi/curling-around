#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Actor;
class Component;
class Camera;

class Scene
{
    public:
        Scene();

        Actor * getRoot();

        Camera * getCamera();
        void setCamera(std::unique_ptr<Camera>);

    private:
        std::unique_ptr<Actor> root;
        std::unique_ptr<Camera> camera;
};

#endif
