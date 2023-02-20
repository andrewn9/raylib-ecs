#ifndef PHYSICS_H
#define PHYSICS_H

#include "../core/system.h"
#include "../components/collider.h"
#include "../components/controller.h"
#include "../components/transform2D.h"
#include "../components/velocity.h"

class Physics : public System {
public:
    void update(float deltaTime){
        for (auto& entityA : entities) {

            Transform2D* transformA = getComponent<Transform2D>(entityA);
            Velocity* velocityA = getComponent<Velocity>(entityA);
            Collider* colliderA = getComponent<Collider>(entityA);

            // Skip entity if mising
            if (!transformA || !velocityA)
                continue;

            transformA->x += velocityA->x * deltaTime;
            transformA->y += velocityA->y * deltaTime;

            if (!colliderA)
                continue;

            colliderA->x = transformA->x;
            colliderA->y = transformA->y;

            for(auto& entityB : entities)
            {
                Transform2D* transformB = getComponent<Transform2D>(entityB);
                Velocity* velocityB = getComponent<Velocity>(entityB);
                Collider* colliderB = getComponent<Collider>(entityB);

                if(entityA == entityB || (!transformB || !velocityB || !colliderB))
                    continue;
                
                if(rectsColliding(colliderA,colliderB))
                    printf("%s","Colliding");

            }

        }
    }

    bool rectsColliding(Collider* rect1Collider, Collider* rect2Collider)
    {
        return
        (
            rect1Collider->x < rect2Collider->x + rect2Collider->width &&
            rect1Collider->x + rect1Collider->width > rect2Collider->x &&
            rect1Collider->y < rect2Collider->y + rect2Collider->height &&
            rect1Collider->y + rect1Collider->height > rect2Collider->y
        );
    }
};

#endif
