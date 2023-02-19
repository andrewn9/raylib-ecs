#ifndef RENDERING_SYSTEM_H
#define RENDERING_SYSTEM_H

#include <vector>

class RenderingSystem : public System {
public:
    // Overrides default system update method
    void update(float deltaTime) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Loop through all entities and render those with RenderableComponents
        for (Entity* entity : entities) {
            PositionComponent* position = getComponent<PositionComponent>(entity);
            RenderableComponent* renderable = getComponent<RenderableComponent>(entity);
            if (position != nullptr && renderable != nullptr) {
                DrawTexture(renderable->texture, (int)position->x, (int)position->y, WHITE);
            }
        }

        EndDrawing();
    }

    // Append entity to list of entities
    void addEntity(Entity* entity) {
        entities.push_back(entity);
    }
private:
    std::vector<Entity*> entities;
};

#endif
