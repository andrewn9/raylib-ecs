#include "rendering.h"

void Rendering::update(float deltaTime) {
    BeginDrawing();

    ClearBackground(RAYWHITE);


    Vector2 focusWorldPos = getComponent<Transform2D>(cameraFocus)->position;
    Vector2 center = Vector2{WIN_WIDTH/2,WIN_HEIGHT/2};
    Vector2 translation = Vector2Subtract(focusWorldPos, center);
    cameraPosition = Vector2Lerp(cameraPosition,translation,0.1);

    for (auto& entity : entities) {

        // Get entity components
        Transform2D* transform = getComponent<Transform2D>(entity);
        Renderable* renderable = getComponent<Renderable>(entity);

        // Skip entity if missing
        if (!transform || !renderable)
            continue;        

        // Original rectangle w/sprite
        Rectangle sourceRec = {0.0f, 0.0f, (float)renderable->texture.width, (float)renderable->texture.height };

        // 'Destination' rectangle, scaled texture
        Rectangle destRec = {transform->position.x,transform->position.y,transform->size.x,transform->size.y};
        Vector2 destCenter = {transform->size.x / 2, transform->size.y / 2 };
        
        destCenter = Vector2Add(destCenter,cameraPosition);

        DrawTexturePro(renderable->texture, sourceRec, destRec, destCenter, transform->rotation, WHITE);
    }
    EndDrawing();
}
