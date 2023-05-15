#include "Collisions.hpp"

#include "PhysicsBody.hpp"
#include "math/Vector.hpp"

void handleSphereToSphereCollision(PhysicsBody &first, PhysicsBody &second)
{
    float minDistance = first.collider.sphere.radius + second.collider.sphere.radius;
    if (distance(first.position, second.position) < minDistance) {
        first.acceleration = Vector3f::zero;
        second.acceleration = Vector3f::zero;

        Vector3f newFirstVelocity = ((first.mass - second.mass) / (first.mass + second.mass)) * first.velocity +
                         ((2 * second.mass) / (first.mass + second.mass)) * second.velocity;

        Vector3f newSecondNelocity = ((2 * first.mass) / (first.mass + second.mass)) * first.velocity +
                          ((second.mass - first.mass) / (first.mass + second.mass)) * second.velocity;

        first.velocity = newFirstVelocity;
        second.velocity = newSecondNelocity;

        // penetration
    }
}
