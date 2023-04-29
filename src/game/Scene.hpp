#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Actor;
class Component;

class Scene
{
    public:
        Scene();

        Actor * const getRoot();

    private:
        std::unique_ptr<Actor> root;
};

#endif
