#include "player.h"

Player::Player(Vector2 pos, Texture2D texture) {
        addComponent(new Transform2D(pos, Vector2{static_cast<float>(texture.width), static_cast<float>(texture.height)},0));
        addComponent(new Renderable(texture));
        addComponent(new Collider(pos, Vector2{static_cast<float>(texture.width), static_cast<float>(texture.height)},0));
        addComponent(new Controller(5.0f));
        addComponent(new Velocity(Vector2{0,0}));
}