#ifndef COLLISIONS_H
#define COLLISIONS_H

class PhysicsBody;

/// @brief Handle collisions between two physics body with sphere colliders
void handleSphereToSphereCollision(PhysicsBody&, PhysicsBody&);

#endif
