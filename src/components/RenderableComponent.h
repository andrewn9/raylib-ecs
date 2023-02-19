#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H

class RenderableComponent : public Component {
public:
    Texture2D texture;

    // Constructor
    RenderableComponent(Texture2D texture_) : texture(texture_) {}
};

#endif
