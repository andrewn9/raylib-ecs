#include "player.h"

Player::Player(float x, float y, Texture2D texture) {

        addComponent(new Transform2D(x, y, static_cast<float>(texture.width), static_cast<float>(texture.height),0));
        addComponent(new Renderable(texture));
        addComponent(new Collider(x,y,static_cast<float>(texture.width), static_cast<float>(texture.height),0));
        addComponent(new Controller(5.0f));
        addComponent(new Velocity(0,0));
}