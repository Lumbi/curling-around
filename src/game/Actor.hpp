#ifndef ACTOR_H
#define ACTOR_H

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "math/Transform.hpp"

#include <memory>
#include <vector>

class Component;
class Scene;

class Actor
{
    public:
        Actor();
        virtual ~Actor();

        Transform & getTransform();
        Matrix4f getLocalToWorldMatrix();
        Vector3f getWorldPosition();

        void update();
        void draw(Scene &);

        const std::vector<std::unique_ptr<Component>>& getComponents() const;
        void attachComponent(std::unique_ptr<Component>);
        void detachComponent(Component *);

        const std::vector<std::unique_ptr<Actor>>& getChildren() const;
        void addChild(std::unique_ptr<Actor>);

    private:
        Transform transform;
        Actor *parent;
        std::vector<std::unique_ptr<Actor>> children;
        std::vector<std::unique_ptr<Component>> components;
};

#endif
