#ifndef COLLIDER_H
#define COLLIDER_H

struct SphereCollider {
    float radius;
};

struct Collider {
    enum class Kind {
        sphere
    };

    Kind kind;

    union {
        SphereCollider sphere;
    };
};

#endif
