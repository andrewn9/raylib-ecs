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
        for (auto& entity : entities) {
            
            Transform2D* transform = getComponent<Transform2D>(entity);
            Velocity* velocity = getComponent<Velocity>(entity);
            Collider* collider = getComponent<Collider>(entity);
            Controller* controller = getComponent<Controller>(entity);

            if(!transform || !velocity || !collider || !controller)
            {
                continue;
            }

            float dx = 0;
            float dy = 0;

            if(IsKeyDown(KEY_UP))
            {
                dy--;
            }
            
            if(IsKeyDown(KEY_DOWN))
            {
                dy++;
            }
            
            if(IsKeyDown(KEY_LEFT))
            {
                dx--;
            }
            
            if(IsKeyDown(KEY_RIGHT))
            {
                dx++;
            }

            Vector2 normalVector = Vector2Normalize(Vector2{dx,dy});
            normalVector = Vector2Scale(normalVector,controller->moveSpeed);
            velocity->x = normalVector.x;
            velocity->y = normalVector.y;

        }
    }
};

#endif
