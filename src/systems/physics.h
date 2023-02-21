#ifndef PHYSICS_H
#define PHYSICS_H

#include <algorithm>
#include "raylib.hpp"
#include "raymath.hpp"
#include "../core/system.h"
#include "../components/collider.h"
#include "../components/controller.h"
#include "../components/transform2D.h"
#include "../components/velocity.h"

// Constants

#define DAMPENING    0.8569f;
#define GRAVITY      10.0f;

class Physics : public System {
public:
    void update(float deltaTime);
    void resolveCollision(Entity* a, Entity* b, Vector2 normal, float penetration, Vector2 n);
    bool AABB(Collider* colliderA, Collider* colliderB);
};

#endif
