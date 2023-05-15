#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

class PhysicsBody;

class Physics {
    public:
        Physics(Physics &) = delete;
        Physics & operator=(Physics &) = delete;

        static Physics & shared();

        void addPhysicsBody(PhysicsBody *);
        void removePhysicsBody(PhysicsBody *);

        void update();

    private:
        Physics();

        std::vector<PhysicsBody *> physicsBodies;
};

#endif
