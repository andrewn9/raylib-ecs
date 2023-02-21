#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../core/component.h"
#include "raylib.hpp"

class Controller : public Component {
public:
    bool grounded;
    float coyote;

    float walkSpeed;
    float jumpHeight;

    Controller(float walkSpeed_, float jumpHeight_) : walkSpeed(walkSpeed_), jumpHeight(jumpHeight_) {}
};

#endif
