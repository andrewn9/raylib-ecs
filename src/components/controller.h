#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../core/component.h"

class Controller : public Component {
public:
    float moveSpeed;

    Controller(float moveSpeed_) : moveSpeed(moveSpeed_) {}
};

#endif
