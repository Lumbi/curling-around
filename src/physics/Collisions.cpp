#include "Collisions.hpp"

#include "PhysicsBody.hpp"
#include "math/Vector.hpp"

void handleSphereToSphereCollision(PhysicsBody &first, PhysicsBody &second)
{
    float currentDistance = distance(first.position, second.position);
    float minDistance = first.collider.sphere.radius + second.collider.sphere.radius;
    if (currentDistance < minDistance) {
        first.acceleration = Vector3f::zero;
        second.acceleration = Vector3f::zero;

        Vector3f newFirstVelocity = ((first.mass - second.mass) / (first.mass + second.mass)) * first.velocity +
                                    ((2 * second.mass) / (first.mass + second.mass)) * second.velocity;

        Vector3f newSecondVelocity = ((2 * first.mass) / (first.mass + second.mass)) * first.velocity +
                                    ((second.mass - first.mass) / (first.mass + second.mass)) * second.velocity;

        first.velocity = newFirstVelocity;
        second.velocity = newSecondVelocity;

        float penetrationAmount = minDistance - currentDistance;
        Vector3f penetration = penetrationAmount * normalize(second.position - first.position);
        first.position += (-0.5f * penetration);
        second.position += (0.5f * penetration);
    }
}
