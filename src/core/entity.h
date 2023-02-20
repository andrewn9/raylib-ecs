#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "component.h"

class Entity {
    public:
        std::vector<Component*> components;
            
        template<typename T>
        void addComponent(T* component) {
            components.push_back(component);
        }

    };
#endif