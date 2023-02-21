#ifndef RENDERING_H
#define RENDERING_H

#include "raylib.hpp"
#include "raymath.hpp"
#include "../core/system.h"
#include "../components/renderable.h"
#include "../components/transform2D.h"
#include "../main.h"

class Rendering : public System {
    public:
        Entity* cameraFocus;
        Vector2 cameraPosition = Vector2{0,0};
        // Draws all current entities with a renderable component
        void update(float deltaTime);
};

#endif