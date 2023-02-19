#include <iostream>

#include "raylib.hpp"

#include "core/component.h"
#include "core/entity.h"
#include "core/system.h"

#include "components/RenderableComponent.h"
#include "components/PositionComponent.h"

#include "systems/RenderingSystem.h"

// Define the maximum number of entities in the game
const int MAX_ENTITIES = 100;

int main() {
    // Create the Raylib window
    const int screenWidth = 640;
    const int screenHeight = 400;
    InitWindow(screenWidth, screenHeight, "Entity-Component-System with Raylib");

    // Create the entities
    Entity* entity1 = new Entity();
    entity1->components.push_back(new PositionComponent(100, 100));
    entity1->components.push_back(new RenderableComponent(LoadTexture("resources/enemy.png")));

    Entity* entity2 = new Entity();
    entity2->components.push_back(new PositionComponent(400, 200));
    entity2->components.push_back(new RenderableComponent(LoadTexture("resources/player.png")));

    // Create the RenderingSystem and add the entities to it
    RenderingSystem renderingSystem;
    renderingSystem.addEntity(entity1);
    renderingSystem.addEntity(entity2);

    // Run the game loop
    const float deltaTime = 1.0f / 60.0f;
    while (!WindowShouldClose()) {
        // Update the systems
        renderingSystem.update(deltaTime);
    }

    // Clean up the entities
    for (Entity* entity : { entity1, entity2 }) {
        for (Component* component : entity->components) {
            delete component;
        }
        delete entity;
    }

    // Close the Raylib window
    CloseWindow();
    return 0;
}
