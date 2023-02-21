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

int main() {
    // Create the Raylib window
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "sick iwndow");
    SetWindowIcon(LoadImage("resources/player.png"));
    SetTargetFPS(MAX_FPS);

    // Create the entities
    Entity* player = new Player(Vector2{0,0},Vector2{32,32},LoadTexture("resources/player.png"));
    Entity* wall1 = new Wall(Vector2{250,250},Vector2{150,150},LoadTexture("resources/wall.png"));
    Entity* wall2 = new Wall(Vector2{300,100},Vector2{32,32},LoadTexture("resources/wall.png"));

    // Create the RenderingSystem and add the entities to it
    Rendering renderingSystem;
    renderingSystem.addEntity(player);
    renderingSystem.addEntity(wall1);
    renderingSystem.addEntity(wall2);

    Input inputSystem;
    inputSystem.addEntity(player);

    Physics physicsSystem;
    physicsSystem.addEntity(player);
    physicsSystem.addEntity(wall1);
    physicsSystem.addEntity(wall2);

    // Run the game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        // Update the systems
        inputSystem.update(deltaTime);
        physicsSystem.update(deltaTime);
        renderingSystem.update(deltaTime);
    }

    // Clean up the entities
    for (Entity* entity : { player, wall1}) {
        for (Component* component : entity->components) {
            delete component;
        }
        delete entity;
    }

    // Close the Raylib window
    CloseWindow();
    return 0;
}
