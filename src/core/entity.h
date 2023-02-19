#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity {
public:
    // Array of component references
    std::vector<Component*> components;
};

#endif
