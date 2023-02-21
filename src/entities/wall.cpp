#include "wall.h"

Wall::Wall(Vector2 pos, Vector2 size, Texture2D texture) {
    addComponent(new Transform2D(pos, size, 0));
    addComponent(new Renderable(texture));
    addComponent(new Collider(pos, size,0,0,true));
}