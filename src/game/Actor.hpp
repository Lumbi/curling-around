#ifndef ACTOR_H
#define ACTOR_H

#include "math/Transform.hpp"

#include <memory>
#include <vector>

class Component;

class Actor
{
    public:
        Transform& getTransform();

        void update();
        void draw();

        const std::vector<std::unique_ptr<Component>>& getComponents() const;
        void attachComponent(std::unique_ptr<Component>);
        void detachComponent(Component *);

        const std::vector<std::unique_ptr<Actor>>& getChildren() const;
        void addChild(std::unique_ptr<Actor>);

    private:
        Transform transform;
        std::vector<std::unique_ptr<Actor>> children;
        std::vector<std::unique_ptr<Component>> components;
};

#endif
