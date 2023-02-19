#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

class PositionComponent : public Component {
public:
    float x;
    float y;

    // Constructor, sets x to x__, respectively
    PositionComponent(float x_, float y_) : x(x_), y(y_) {}
};

#endif
