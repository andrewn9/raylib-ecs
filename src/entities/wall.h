#ifndef WALL_H
#define WALL_H

#include "raylib.hpp"
#include "../core/entity.h"
#include "../components/collider.h"
#include "../components/renderable.h"
#include "../components/transform2D.h"

class Wall : public Entity {
    public:
        Wall(Vector2 pos, Vector2 size, Texture2D texture);
};

#endif
