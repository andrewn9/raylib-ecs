#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/component.h"
#include "raylib.hpp"
#include <cstdio>

class Collider : public Component {
    public:
        Vector2 position;
        Vector2 size;

        float density; // 0 = infinite mass | 1 = standard
        float restitution; // 0 = rigid | 1 = elastic

        bool isSolid;

        Collider(Vector2 position_, Vector2 size_, float density_ = 1,  float restitution_ = 0, bool isSolid_ = true)
            : position(position_), size(size_), density(density_), restitution(restitution_) , isSolid(isSolid_) 
            {}
};

#endif
