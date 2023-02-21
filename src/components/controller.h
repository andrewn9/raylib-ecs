#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../core/component.h"
#include "raylib.hpp"

class Controller : public Component {
public:
    float moveSpeed;

    Controller(float moveSpeed_) : moveSpeed(moveSpeed_) {}
};

#endif
