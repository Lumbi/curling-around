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

        float firstSpeed = first.velocity.length();
        float secondSpeed = second.velocity.length();
        float massSum = first.mass + second.mass;
        float momentumSum = first.mass * firstSpeed + second.mass * secondSpeed;

        float cr = 0.85f; // Coefficient of restitution

        // Inelastic collision
        float newFirstSpeed = (cr * second.mass * (secondSpeed - firstSpeed) + momentumSum) / massSum;
        float newSecondSpeed = (cr * first.mass * (firstSpeed - secondSpeed) + momentumSum) / massSum;

        // Ideally, the momentum perpendicular to the collision tangent should be conserved
        Vector3f normal = normalize(first.position - second.position);
        first.velocity = newFirstSpeed * normal;
        second.velocity = newSecondSpeed * normal * -1.f;

        // De-penetrate the colliders to avoid subsequent re-collisions
        float penetrationAmount = minDistance - currentDistance;
        Vector3f penetration = penetrationAmount * normalize(second.position - first.position);
        first.position += (-0.5f * penetration);
        second.position += (0.5f * penetration);
    }
}
