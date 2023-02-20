#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../core/component.h"
#include "raylib.hpp"

class Renderable : public Component {
    public:
        Texture2D texture;
        Renderable(Texture2D texture_) : texture(texture_) {}
};
#endif
