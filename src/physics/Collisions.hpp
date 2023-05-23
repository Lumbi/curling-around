#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <functional>

class PhysicsBody;

// typedef void(*CollisionCallback)(PhysicsBody&, PhysicsBody&);

/// @brief Handle collisions between two physics body with sphere colliders.
/// @return Whether or not two bodies collided.
bool handleSphereToSphereCollision(PhysicsBody&, PhysicsBody&);

#endif
