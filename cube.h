#pragma once
#include "shape3D.h"
#include "physics.h"

class Cube : public Shape3D , public Physics
{
public:
    Cube(float s_width);
    float get_number_of_indices() const {return 36;}
    
    void bind_vao();
    void update_collision_box();
    void move(float dx, float dy, float dz, float dt);
    
    void not_applying_left_force() { pushing_left = false; }
    void not_applying_right_force() { pushing_right = false; }

    void applyGravity(float dt);
    void update_horizontal_movement(float dt);

    AABB& get_collision_box() {return CollisionBox; }
private:
    //Texture texture;
    AABB CollisionBox;
    float sideLength;
};