#ifndef PHYSICS_H
#define PHYSICS_H

#include "PhysicsBody.hpp"

#include <vector>
#include <unordered_map>

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

        /// @brief Get the list of physics bodies in contact with a physics body during the current frame.
        /// @param id The identifier of the physics body to get contacts from.
        const std::vector<PhysicsBody *> & getContacts(PhysicsBody::ID id);

        // Disable copy-constructor and copy-assignment operator.
        Physics(Physics &) = delete;
        Physics & operator=(Physics &) = delete;

    private:
        Physics();

        std::vector<PhysicsBody *> physicsBodies;
        std::unordered_map<PhysicsBody::ID, std::vector<PhysicsBody *>> contacts;
};

#endif
