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

#include "main.h"

int main() {
    // Create the Raylib window
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Entity-Component-System with Raylib");

    // Create the entities
    Entity* entity1 = new Player(Vector2{100,100},LoadTexture("resources/player.png"));

    // Entity* entity1 = new Entity();
    // entity1->addComponent(new Transform2D(Vector2{200,200},Vector2{32,32},0));
    // entity1->addComponent(new Renderable(LoadTexture("resources/enemy.png")));
    // entity1->addComponent(new Collider(Vector2{200,200},Vector2{32,32}));
    // entity1->addComponent(new Velocity(Vector2{5,0}));

    Entity* entity2 = new Entity();
    entity2->addComponent(new Transform2D(Vector2{400,200},Vector2{32,32},0));
    entity2->addComponent(new Renderable(LoadTexture("resources/enemy.png")));
    entity2->addComponent(new Collider(Vector2{400,200},Vector2{32,32}));
    entity2->addComponent(new Velocity(Vector2{-1,0}));

    // Create the RenderingSystem and add the entities to it
    Rendering renderingSystem;
    renderingSystem.addEntity(entity1);
    renderingSystem.addEntity(entity2);

    Input inputSystem;
    inputSystem.addEntity(entity1);

    Physics physicsSystem;
    physicsSystem.addEntity(entity1);
    physicsSystem.addEntity(entity2);

    // Run the game loop
    const float deltaTime = 1.0f / 240.0f;
    while (!WindowShouldClose()) {
        // Update the systems
        inputSystem.update(deltaTime);
        physicsSystem.update(deltaTime);
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
