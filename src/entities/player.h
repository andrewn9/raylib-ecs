#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.hpp"
#include "../core/entity.h"
#include "../components/collider.h"
#include "../components/controller.h"
#include "../components/renderable.h"
#include "../components/transform2D.h"
#include "../components/velocity.h"

class Player : public Entity {
    public:
        Player(Vector2 pos, Vector2 size, Texture2D texture);
};

#endif
