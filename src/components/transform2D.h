#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H

#include "../core/component.h"

class Transform2D : public Component {
    public:
        float x;
        float y;

        float width;
        float height;

        float rotation;

        Transform2D(float x_, float y_, float width_, float height_, float rotation_) : x(x_), y(y_), width(width_), height(height_), rotation(rotation_) {}
};
#endif
