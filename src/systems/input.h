#ifndef INPUT_H
#define INPUT_H

#include "../core/system.h"
#include "raymath.hpp"

#include "../core/system.h"
#include "../components/collider.h"
#include "../components/controller.h"
#include "../components/transform2D.h"
#include "../components/velocity.h"

class Input : public System {

public:
    void update(float deltaTime) {
        // Loop through all entities
        for (auto& entity : entities) {
            
            Transform2D* transform = getComponent<Transform2D>(entity);
            Velocity* velocity = getComponent<Velocity>(entity);
            Collider* collider = getComponent<Collider>(entity);
            Controller* controller = getComponent<Controller>(entity);

            // Skip entity if missing any components
            if(!transform || !velocity || !collider || !controller)
            {
                continue;
            }

            Vector2 moveVector = Vector2{0,0};

            if(IsKeyDown(KEY_UP) && controller->grounded)
                moveVector.y-=controller->jumpHeight;
            if(IsKeyDown(KEY_LEFT))
                moveVector.x-=controller->walkSpeed;
            if(IsKeyDown(KEY_RIGHT))
                moveVector.x+=controller->walkSpeed;

            if(Vector2Length(moveVector) == 0)
                continue;

            velocity->velocity = Vector2Add(velocity->velocity,moveVector);
            
        }
    }
};

#endif
