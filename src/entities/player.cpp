#include "player.h"

Player::Player(Vector2 pos, Vector2 size, Texture2D texture) {
        addComponent(new Transform2D(pos, size ,0));
        addComponent(new Renderable(texture));
        addComponent(new Collider(pos, size));
        addComponent(new Controller(55.0f));
        addComponent(new Velocity(Vector2{0,0}));
}