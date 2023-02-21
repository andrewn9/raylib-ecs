#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/component.h"
#include "raylib.hpp"

class Collider : public Component {
    public:
        Vector2 position;
        Vector2 size;

        bool isSolid;
        float density;

        Collider(Vector2 position_, Vector2 size_, bool isSolid_ = true, float density_ = 1)
            : position(position_), size(size_), isSolid(isSolid_) , density(density_){}
};

#endif
