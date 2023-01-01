#pragma once
#include "physics.h"
#include "shape3D.h"
#include <iostream>

class Collisions
{
public:
    static bool aabb_is_colliding(AABB object1, AABB object2);
    static float get_aabb_collision_displacement(AABB objectA, AABB objectB);
    static void resolve_aabb_collision(AABB& objectA, AABB& ObjectB, Shape3D& shape);
    static void resolve_aabb_x_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float xVelocity);
    static void resolve_aabb_y_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float yVelocity);
    static void resolve_aabb_z_collisions(AABB& objectA, AABB& objectB, Shape3D& shape, float zVelocity);
private:
    
};


