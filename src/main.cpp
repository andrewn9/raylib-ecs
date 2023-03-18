#include <iostream>

#include "raylib.hpp"

#include "core/component.h"
#include "core/entity.h"
#include "core/system.h"

#include "components/collider.h"
#include "components/controller.h"
#include "components/renderable.h"
#include "components/transform2D.h"
#include "components/velocity.h"

#include "systems/input.h"
#include "systems/physics.h"
#include "systems/rendering.h"

#include "entities/player.h"
#include "entities/wall.h"

#include "main.h"

int tilemap[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main() {
    // Create the Raylib window
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "sick iwndow");
    SetWindowIcon(LoadImage("resources/player.png"));
    SetTargetFPS(MAX_FPS);

    // Create the entities
    std::vector<Entity*> allEntities;
    Entity* player = new Player(Vector2{0,0},Vector2{32,32},LoadTexture("resources/player.png"),1);
    allEntities.push_back(player);

    std::vector<Entity*> walls;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Check if the current tile is a wall
            if (tilemap[i][j] == 1) {
                // Calculate the position of the tile
                Vector2 position = Vector2{i * 32.0f, j * 32.0f};
                Entity* wall = new Wall(position, Vector2{32,32}, LoadTexture("resources/wall.png"), i * 10 + j + 2);
                allEntities.push_back(wall);
                walls.push_back(wall);
            }
        }
    }

    // Create the RenderingSystem and add the entities to it
    Rendering renderingSystem;
    renderingSystem.cameraFocus = player;
    renderingSystem.addEntity(player);
    for (Entity* wall : walls) {
        renderingSystem.addEntity(wall);
    }

    Input inputSystem;
    inputSystem.addEntity(player);

    Physics physicsSystem;
    physicsSystem.addEntity(player);
    for (Entity* wall : walls) {
        physicsSystem.addEntity(wall);
    }

    // Run the game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        // Update the systems
        physicsSystem.update(deltaTime);
        inputSystem.update(deltaTime);
        renderingSystem.update(deltaTime);
    }

    // Clean up the entities
    for (Entity* entity : allEntities) {
        for (Component* component : entity->components) {
            delete component;
        }
        delete entity;
    }

    // Close the Raylib window
    CloseWindow();
    return 0;
}
