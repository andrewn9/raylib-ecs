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

            if (!colliderA)
                continue;

            colliderA->position = transformA->position;    

            for(auto& entityB : entities)
            {
                Transform2D* transformB = getComponent<Transform2D>(entityB);
                Velocity* velocityB = getComponent<Velocity>(entityB);
                Collider* colliderB = getComponent<Collider>(entityB);

                if((entityA == entityB)||!transformB || !colliderB)
                     continue;

                if(rectsColliding(colliderA,colliderB))
                {    
                    
                    // // Vector from A to B
                    Vector2 n = Vector2Subtract(velocityB->velocity,velocityA->velocity);

                    /**
                     *      min_____________________
                     *      |                       |
                     *      |                       |
                     *      |          pos          |
                     *      |                       |
                     *      |_______________________max
                     * 
                    */

                    // Calculate minimum and maximum points for each collider
                    Vector2 a_min = Vector2{colliderA->position.x - (colliderA->size.x/2), colliderA->position.y - (colliderA->size.y/2)};
                    Vector2 a_max = Vector2{colliderA->position.x + (colliderA->size.x/2), colliderA->position.y + (colliderA->size.y/2)};

                    Vector2 b_min = Vector2{colliderB->position.x - (colliderB->size.x/2), colliderB->position.y - (colliderB->size.y/2)};
                    Vector2 b_max = Vector2{colliderB->position.x + (colliderB->size.x/2), colliderB->position.y + (colliderB->size.y/2)};

                    // Calculate half extents along x axis for each object 
                    float a_extent = (a_max.x - a_min.x) / 2;
                    float b_extent = (b_max.x - b_min.x) / 2;

                    // Calculate overlap on x axis
                    float x_overlap = a_extent + b_extent - abs(n.x);

                    float penetration;
                    Vector2 normal;

                    // SAT test on x axis 
                    if(x_overlap > 0)
                    {
                        // Calculate half extents along x axis for each object 
                        float a_extent = (a_max.y - a_min.y) / 2;
                        float b_extent = (b_max.y - b_min.y) / 2;
                    
                        // Calculate overlap on y axis 
                        float y_overlap = a_extent + b_extent - abs(n.y);
                    
                        // SAT test on y axis 
                        if(y_overlap > 0)
                        {
                            printf("x_overlap %f", x_overlap);
                            printf("y_overlap %f\n\n", y_overlap);
                            // Find out which axis is axis of least penetration 
                            if(x_overlap > y_overlap)
                            {
                                // Point towards B knowing that n points from A to B 
                                if(n.x < 0)
                                    normal = Vector2{-1, 0};
                                else
                                    normal = Vector2{0, 0};
                                penetration = x_overlap;
                                ResolveCollision(entityA,entityB, normal, penetration);
                            }
                            else
                            {
                                // Point toward B knowing that n points from A to B 
                                if(n.y < 0)
                                    normal = Vector2{ 0, -1};
                                else
                                    normal = Vector2{ 0, 1 };
                                penetration = y_overlap;
                                ResolveCollision(entityA,entityB, normal, penetration);
                            }
                        }
                    }
                }

                transformA->position = Vector2Add(transformA->position,Vector2Scale(velocityA->velocity,deltaTime));
            }
        }
    }
    void ResolveCollision(Entity* a, Entity*b, Vector2 normal, float penetration)
    {   

        Velocity* velocityA = getComponent<Velocity>(a);
        Collider* colliderA = getComponent<Collider>(a);
    
        Velocity* velocityB = getComponent<Velocity>(b);
        Collider* colliderB = getComponent<Collider>(b);

        // Calculate relative velocity 
        Vector2 rv = Vector2Subtract(velocityB->velocity, velocityA->velocity);
        
        printf("normalx%f, normaly%f\n", normal.x, normal.y);
        // printf("relativex%f, relativey%f\n", rv.x, rv.y);

        // Calculate relative velocity in terms of the normal direction 
        float velAlongNormal = Vector2DotProduct(rv,normal);
        //printf("%f\n",velAlongNormal);
        // // Do not resolve if velocities are separating 
        if(velAlongNormal>0)
             return;
        

        // // Calculate restitution 
        float e = 0.5;

        float aMass = colliderA->size.x * colliderA->size.y;
        float bMass = colliderB->size.x * colliderB->size.y;

        // // Calculate impulse scalar 
        float j = -(1.0+e) * velAlongNormal;
        j/= 1.0 / aMass + 1.0 / bMass;

        // // Apply impulse 

        Vector2 impulse = Vector2Scale(normal,j);
        
        Vector2 da = Vector2Scale(impulse,1/aMass);
        Vector2 db = Vector2Scale(impulse,1/bMass);

        velocityA->velocity = Vector2Subtract(velocityA->velocity, da);
        velocityB->velocity = Vector2Add(velocityB->velocity, db);
    }

    bool rectsColliding(Collider* rect1Collider, Collider* rect2Collider)
    {
        return
        (
            rect1Collider->position.x < rect2Collider->position.x + rect2Collider->size.x &&
            rect1Collider->position.x + rect1Collider->size.x > rect2Collider->position.x &&
            rect1Collider->position.y < rect2Collider->position.y + rect2Collider->size.y &&
            rect1Collider->position.y + rect1Collider->size.y > rect2Collider->position.y
        );
    }
};

#endif
