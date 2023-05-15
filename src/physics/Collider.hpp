#ifndef COLLIDER_H
#define COLLIDER_H

struct SphereCollider {
    float radius;
};

union Collider {
    SphereCollider sphere;
};

#endif
