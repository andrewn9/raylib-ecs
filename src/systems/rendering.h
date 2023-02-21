#ifndef RENDERING_H
#define RENDERING_H

#include "raylib.hpp"
#include "../core/system.h"
#include "../components/renderable.h"
#include "../components/transform2D.h"

class Rendering : public System {
    public:
         void update(float deltaTime) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (auto& entity : entities) {
                Transform2D* transform = getComponent<Transform2D>(entity);
                Renderable* renderable = getComponent<Renderable>(entity);

                // Skip entity if missing
                if (!transform || !renderable)
                    continue;

                Rectangle sourceRec = {0.0f, 0.0f, (float)renderable->texture.width, (float)renderable->texture.height };

                Rectangle destRec = {transform->position.x,transform->position.y,transform->size.x,transform->size.y};
                Vector2 destCenter = { transform->size.x / 2, transform->size.y / 2 };

                DrawTexturePro(renderable->texture, sourceRec, destRec, destCenter, transform->rotation, WHITE);
            }
            EndDrawing();
        }
};

#endif
