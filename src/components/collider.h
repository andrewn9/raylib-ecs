#ifndef COLLIDER_H
#define COLLIDER_H

#include "../core/component.h"

class Collider : public Component {
    public:
        float x;
        float y;

        float width;
        float height;

        bool isSolid;

        Collider(float x_, float y_,float width_, float height_, bool isSolid_ = true)
            : x(x_), y(y_), width(width_), height(height_), isSolid(isSolid_) {}
};

#endif
