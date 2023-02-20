#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "component.h"
#include "entity.h"

class System {
    public:
        // Deconstructor
        virtual ~System() {}

        // Update function
        virtual void update(float deltaTime) = 0;

        // Function to get the component of an entity in the system
        template<typename T>
        T* getComponent(Entity* entity) {
            for (Component* component : entity->components) {
                T* result = dynamic_cast<T*>(component);
                if (result != nullptr) {
                    return result;
                }
            }
            return nullptr;
        }

        // Add an entity to the system
        void addEntity(Entity* entity) {
            entities.push_back(entity);
        }
        
        // Get all entities in the system
        const std::vector<Entity*>& getEntities() const {
            return entities;
        }

    protected:
        std::vector<Entity*> entities;
    };

#endif