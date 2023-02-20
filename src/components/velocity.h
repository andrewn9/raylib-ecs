#ifndef VELOCITY_H
#define VELOCITY_H

#include "../core/component.h"

class Velocity : public Component {
    public:
        float x;
        float y;

        Velocity(float x_, float y_)
            : x(x_), y(y_) {}
};

#endif
