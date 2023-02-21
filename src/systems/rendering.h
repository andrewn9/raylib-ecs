#ifndef RENDERING_H
#define RENDERING_H

#include "raylib.hpp"
#include "../core/system.h"
#include "../components/renderable.h"
#include "../components/transform2D.h"

class Rendering : public System {
    public:
        // Draws all current entities with a renderable component
        void update(float deltaTime);
};

#endif