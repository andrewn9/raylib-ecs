#include "physics.h"

void Physics::update(float deltaTime){
    // Loop through all entities
    for (auto& entityA : entities) {
        // Get components
        Transform2D* transformA = getComponent<Transform2D>(entityA);
        Velocity* velocityA = getComponent<Velocity>(entityA);
        Collider* colliderA = getComponent<Collider>(entityA);

        // Skip entity if mising
        if (!transformA || !velocityA)
            continue;

        // Simply add velocity if there is no collider
        if (!colliderA){
            transformA->position = Vector2Add(transformA->position,Vector2Scale(velocityA->velocity,deltaTime));
            continue;
        }   

        for(auto& entityB : entities)
        {
            // Get components for the entity checking against
            Transform2D* transformB = getComponent<Transform2D>(entityB);
            Collider* colliderB = getComponent<Collider>(entityB);
    
            // Skip if entity is the same or missing components
            if((entityA == entityB)||!transformB || !colliderB)
                    continue;

            // If colliders are in bounds of each other
            if(AABB(colliderA,colliderB))
            {    
                printf("%s\n","colliding");
                
                // // Vector from A to B
                Vector2 n = Vector2Subtract(colliderB->position,colliderA->position);

                // Calculate minimum and maximum points for each collider, smallest and highest vector points, corners
                Vector2 a_min = Vector2{colliderA->position.x - (colliderA->size.x/2), colliderA->position.y - (colliderA->size.y/2)};
                Vector2 a_max = Vector2{colliderA->position.x + (colliderA->size.x/2), colliderA->position.y + (colliderA->size.y/2)};

                Vector2 b_min = Vector2{colliderB->position.x - (colliderB->size.x/2), colliderB->position.y - (colliderB->size.y/2)};
                Vector2 b_max = Vector2{colliderB->position.x + (colliderB->size.x/2), colliderB->position.y + (colliderB->size.y/2)};


                // Calculate half extents along x axis for each object 
                float a_extent = (a_max.x - a_min.x) / 2;
                float b_extent = (b_max.x - b_min.x) / 2;

                // Calculate overlap on x axis
                float x_overlap = a_extent + b_extent - abs(n.x);

                float penetration;
                Vector2 normal;

                // Seperating Axis Test (SAT) test on x axis 
                // If x_overlap is over O, that means the 2 objects are overlapping along the x-axis
                if(x_overlap > 0)
                {
                    // Calculate half extents along x axis for each object 
                    float a_extent = (a_max.y - a_min.y) / 2;
                    float b_extent = (b_max.y - b_min.y) / 2;
                
                    // Calculate overlap on y axis 
                    float y_overlap = a_extent + b_extent - abs(n.y);
                
                    // SAT test on y axis 
                    if(y_overlap > 0)
                    {
                        // Find out which axis is axis of least penetration 
                        if(x_overlap < y_overlap)
                        {
                            // Point towards B knowing that n points from A to B 
                            if(n.x < 0)
                                normal = Vector2{-1, 0};
                            else
                                normal = Vector2{1, 0};
                            penetration = x_overlap;
                        }
                        else
                        {
                            // Point toward B knowing that n points from A to B 
                            if(n.y < 0)
                                normal = Vector2{ 0, -1};
                            else
                                normal = Vector2{ 0, 1};
                            penetration = y_overlap;
                        }
                        resolveCollision(entityA,entityB, normal, penetration, n);
                    }
                    
                }
            }
        }
        transformA->position = Vector2Add(transformA->position,Vector2Scale(velocityA->velocity,deltaTime));
        colliderA->position = transformA->position;
        velocityA->velocity = Vector2Scale(velocityA->velocity, 0.8);
    }
}
void Physics::resolveCollision(Entity* a, Entity*b, Vector2 normal, float penetration, Vector2 n)
{   
    Transform2D* transformA = getComponent<Transform2D>(a);
    Transform2D* transformB = getComponent<Transform2D>(b);

    Vector2 velocityA = getComponent<Velocity>(a) ?  getComponent<Velocity>(a)->velocity : Vector2 {0,0} ;
    Collider* colliderA = getComponent<Collider>(a);

    Vector2 velocityB = getComponent<Velocity>(b) ?  getComponent<Velocity>(b)->velocity : Vector2 {0,0} ;
    Collider* colliderB = getComponent<Collider>(b);

    // Calculate relative velocity 
    Vector2 rv = Vector2Subtract(velocityB, velocityA);

    // Calculate relative velocity in terms of the normal direction 
    float velAlongNormal = Vector2DotProduct(rv,normal);

    // // Do not resolve if velocities are separating 
    if(velAlongNormal>0)
            return;
    

    // // Calculate restitution 
    float e = std::min(colliderA->restitution,colliderB->restitution);

    float aMass = (colliderA->size.x * colliderA->size.y) * colliderA->density;
    float bMass = (colliderB->size.x * colliderB->size.y) * colliderB->density;

    float a_invMass = colliderA->density == 0.0f ? 0 : 1/aMass;
    float b_invMass = colliderB->density == 0.0f ? 0 : 1/bMass;

    // // Calculate impulse scalar 
    float j = -(1.0+e) * velAlongNormal;
    j/= a_invMass + b_invMass;

    // // Apply impulse 
    Vector2 impulse = Vector2Scale(normal,j);
    
    Vector2 da = Vector2Scale(impulse,1/aMass);
    Vector2 db = Vector2Scale(impulse,1/bMass);

    // Only affect the entity if it has mass, ie. not a wall
    if(a_invMass > 0)
        velocityA = Vector2Subtract(velocityA, da);
    if(b_invMass > 0)
        velocityB = Vector2Add(velocityB, db);

    // Apply positional correction
    Vector2 correction = Vector2Scale(n, (fmaxf(penetration - SLOP, 0.0f) / (a_invMass + b_invMass)) * PEN_REDUX);
    transformA->position =  Vector2Subtract(colliderA->position, Vector2Scale(correction, a_invMass));
    transformB->position =  Vector2Add(colliderB->position, Vector2Scale(correction, b_invMass));
    colliderA->position = transformA->position;
    colliderB->position = transformB->position;
}

bool Physics::AABB(Collider* colliderA, Collider* colliderB)
{
    return
    (
        (colliderA->position.x - colliderA->size.x / 2.0f) < (colliderB->position.x + colliderB->size.x / 2.0f) &&
        (colliderA->position.x + colliderA->size.x / 2.0f) > (colliderB->position.x - colliderB->size.x / 2.0f) &&
        (colliderA->position.y - colliderA->size.y / 2.0f) < (colliderB->position.y + colliderB->size.y / 2.0f) &&
        (colliderA->position.y + colliderA->size.y / 2.0f) > (colliderB->position.y - colliderB->size.y / 2.0f)
    );
}
