#pragma once
#include "shape3D.h"
#include "texture.h"
#include "physics.h"

class Cube : public Shape3D , public Physics
{
public:
    Cube(float s_width);
    float get_number_of_indices() const {return 36;}
    
    void bind_vao();
    void applyGravity(float dt);
    void update();
    
    AABB& get_collision_box() {return CollisionBox; }
private:
    //Texture texture;
    AABB CollisionBox;
    float sideLength;
};