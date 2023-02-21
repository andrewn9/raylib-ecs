#ifndef VELOCITY_H
#define VELOCITY_H

#include "../core/component.h"
#include "raylib.hpp"

class Velocity : public Component {
    public:
        Vector2 velocity;
        Velocity(Vector2 velocity_) : velocity(velocity_) {}
};

#endif
