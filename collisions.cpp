#include "collisions.h"
#include "transformations.h"

bool Collisions::aabb_is_colliding(AABB object1, AABB object2)
{
    
    if (abs(object1.center[0] - object2.center[0]) > (object1.r[0] + object2.r[0])) return 0;
    if (abs(object1.center[1] - object2.center[1]) > (object1.r[1] + object2.r[1])) return 0;
    if (abs(object1.center[2] - object2.center[2]) > (object1.r[2] + object2.r[2])) return 0;
    return 1;
}

void Collisions::resolve_aabb_collision(AABB& ObjectA, AABB& ObjectB, Shape3D& shape)
{
    // Y Axis Collision
    
    if (abs(ObjectA.center[1] - ObjectB.center[1]) < (ObjectA.r[1] + ObjectB.r[1]))
    {
        ObjectA.center[1] += (ObjectA.r[1] + ObjectB.r[1]) - (abs(ObjectA.center[1] - ObjectB.center[1]));
        Transformations::translate3D(shape, 0, ObjectA.center[1] - shape.get_position_vector().y, 0);
        std::printf("Y Offset: %.2f\n", (ObjectA.r[1] + ObjectB.r[1]) - (abs(ObjectA.center[1] - ObjectB.center[1])));
    }

    // X Axis Collision
    if (abs(ObjectA.center[0] - ObjectB.center[0]) < (ObjectA.r[0] + ObjectB.r[0]))
    {
        ObjectA.center[0] += (ObjectA.r[0] + ObjectB.r[0]) - (abs(ObjectA.center[0] - ObjectB.center[0]));
        Transformations::translate3D(shape, ObjectA.center[0] - shape.get_position_vector().x, 0, 0);
        //std::printf("X Offset: %.2f\n", (ObjectA.r[0] + ObjectB.r[0]) - (abs(ObjectA.center[0] - ObjectB.center[0])));
    }   

    // Z Axis Collision
    if (abs(ObjectA.center[2] - ObjectB.center[2]) < (ObjectA.r[2] + ObjectB.r[2]))
    {
        ObjectA.center[2] += (ObjectA.r[2] + ObjectB.r[2] - (abs(ObjectA.center[2] - ObjectB.center[2])));
        Transformations::translate3D(shape, 0, 0, ObjectA.center[2] - shape.get_position_vector().z);
        //std::printf("Z Offset: %.2f\n", (ObjectA.r[2] + ObjectB.r[2]) - (abs(ObjectA.center[2] - ObjectB.center[2])));
    }
}
void Collisions::resolve_aabb_x_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float xVelocity)
{
    if (abs(objectA.center[0] - objectB.center[0]) < (objectA.r[0] + objectB.r[0]))
    {
        if (xVelocity < 0)
            objectA.center[0] += ( objectA.r[0] + objectB.r[0]) - (abs(objectA.center[0] - objectB.center[0]));
        if (xVelocity > 0)
            objectA.center[0] -= ( objectA.r[0] + objectB.r[0]) - (abs(objectA.center[0] - objectB.center[0]));
        Transformations::translate3D(shape, objectA.center[0] - shape.get_position_vector().x, 0, 0);
        //std::printf("X Offset: %.2f\n", (ObjectA.r[0] + ObjectB.r[0]) - (abs(ObjectA.center[0] - ObjectB.center[0])));
    } 
}

void Collisions::resolve_aabb_y_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float yVelocity)
{
    if (abs(objectA.center[1] - objectB.center[1]) < (objectA.r[1] + objectB.r[1]))
    {
        if (yVelocity < 0)
            objectA.center[1] += ( objectA.r[1] + objectB.r[1]) - (abs(objectA.center[1] - objectB.center[1]));
        if (yVelocity > 0)
            objectA.center[1] -= ( objectA.r[1] + objectB.r[1]) - (abs(objectA.center[1] - objectB.center[1]));
        Transformations::translate3D(shape, 0, objectA.center[1] - shape.get_position_vector().y, 0);
        //std::printf("X Offset: %.2f\n", (ObjectA.r[0] + ObjectB.r[0]) - (abs(ObjectA.center[0] - ObjectB.center[0])));
    } 
}
void Collisions::resolve_aabb_z_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float zVelocity)
{
    if (abs(objectA.center[2] - objectB.center[2]) < (objectA.r[2] + objectB.r[2]))
    {
        if (zVelocity < 0)
            objectA.center[2] += ( objectA.r[2] + objectB.r[2]) - (abs(objectA.center[2] - objectB.center[2]));
        if (zVelocity > 0)
            objectA.center[2] -= ( objectA.r[2] + objectB.r[2]) - (abs(objectA.center[2] - objectB.center[2]));
        Transformations::translate3D(shape, 0, 0, objectA.center[2] - shape.get_position_vector().z);
        //std::printf("X Offset: %.2f\n", (ObjectA.r[0] + ObjectB.r[0]) - (abs(ObjectA.center[0] - ObjectB.center[0])));
    }
}   