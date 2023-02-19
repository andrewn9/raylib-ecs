#ifndef SYSTEM_H
#define SYSTEM_H

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

};

#endif