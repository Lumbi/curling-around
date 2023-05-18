#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>

class PhysicsBody;

/// @brief A singleton to run the physics simulation.
class Physics {
    public:
        /// @brief Get the shared singleton instance.
        static Physics & shared();


        /// @brief Add a physics body to the simulation.
        void addPhysicsBody(PhysicsBody *);

        /// @brief Remove a physics body from the simulation.
        void removePhysicsBody(PhysicsBody *);

        /// @brief Update the simulation.
        void update();

        // Disable copy-constructor and copy-assignment operator.
        Physics(Physics &) = delete;
        Physics & operator=(Physics &) = delete;

    private:
        Physics();

        std::vector<PhysicsBody *> physicsBodies;
};

#endif
