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

            if(IsKeyDown(KEY_UP))
                moveVector.y--;
            if(IsKeyDown(KEY_DOWN))
                moveVector.y++;
            if(IsKeyDown(KEY_LEFT))
                moveVector.x--;
            if(IsKeyDown(KEY_RIGHT))
                moveVector.x++;

            if(Vector2Length(moveVector) == 0)
                continue;

            Vector2 normalVector = Vector2Normalize(moveVector);
            normalVector = Vector2Scale(normalVector,controller->moveSpeed);
            //printf("VELOCITXE%f, VELOCITYY%f\n\n", velocity->velocity.x, velocity->velocity.y);
            velocity->velocity = Vector2Add(velocity->velocity,normalVector);
            
        }
    }
};

#endif
