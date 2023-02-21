#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "../core/component.h"
#include "raylib.hpp"

class Transform2D : public Component {
    public:
        Vector2 position;
        Vector2 size;

        float rotation;

        Transform2D(Vector2 position_, Vector2 size_, float rotation_) :position(position_), size(size_), rotation(rotation_) {}
};

#endif
