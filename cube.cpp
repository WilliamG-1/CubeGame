#include "cube.h"
#include <math.h>
#include <iostream>
Cube::Cube(float s_width) 
    //: //texture("Assets/container2.png")
{
    mass = 20; // (kilograms)
    normal = mass * Gravity();
    friction_coefficient = 0.1;

    sideLength = s_width; // <-- Can you be less confusing?? Lol
    float half_side = sideLength/2;
    for (int i = 0; i < 3; i++)
        CollisionBox.r[i] = half_side; // Set all radii to half_side 
    
    // float vertices[] = {
    //     // Front face                      // Normal
    //     -half_side, -half_side, half_side, 0, 0, 0, // Bottom Left  (0)
    //     -half_side,  half_side, half_side, 0, 0, 0, // Top Left     (1)
    //      half_side, -half_side, half_side, 0, 0, 0, // Bottom Right (2)
    //      half_side,  half_side, half_side, 0, 0, 0, // Top Right    (3)

    //      // Back Face 
    //     -half_side, -half_side, -half_side, 0, 0, 0, // Bottom Left  (4)
    //     -half_side,  half_side, -half_side, 0, 0, 0, // Top Left     (5)
    //      half_side, -half_side, -half_side, 0, 0, 0, // Bottom Right (6)
    //      half_side,  half_side, -half_side, 0, 0, 0,  // Top Right    (7)

    //       half_side, 0.0f, 0.0f           ,  1.0f, 0, 0,
    //      -half_side, 0.0f, 0.0f           , -1.0f, 0, 0,
    //      0.0f,  half_side, 0.0f           , 0,  1.0f, 0,
    //      0.0f, -half_side, 0.0f           , 0, -1.0f, 0,
    //      0.0f, 0.0f,  half_side           , 0, 0,  1.0f,
    //      0.0f, 0.0f, -half_side           , 0, 0, -1.0f
    // };
    float nVertices[] {
        // Front Face                      Normal Vector        Texture Coordinates
        -half_side, -half_side, half_side, 0.0f, 0.0f,  1.0f,   0.0f, 0.0f,          // (0)
        -half_side,  half_side, half_side, 0.0f, 0.0f,  1.0f,   0.0f, 1.0f,
         half_side, -half_side, half_side, 0.0f, 0.0f,  1.0f,   1.0f, 0.0f,
         half_side,  half_side, half_side, 0.0f, 0.0f,  1.0f,   1.0f, 1.0f,

        // Top Face
        -half_side, half_side,  half_side, 0.0f,  1.0f, 0.0f,   0.0f, 1.0f,         // (4)
        -half_side, half_side, -half_side, 0.0f,  1.0f, 0.0f,   0.0f, 0.0f,
         half_side, half_side,  half_side, 0.0f,  1.0f, 0.0f,   1.0f, 1.0f,
         half_side, half_side, -half_side, 0.0f,  1.0f, 0.0f,   1.0f, 0.0f,

        // Right Face
        half_side,  half_side,  half_side,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,        // (8)
        half_side,  half_side, -half_side,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        half_side, -half_side,  half_side,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
        half_side, -half_side, -half_side,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        // Back Face
        -half_side, -half_side, -half_side, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f,        // (12)
        -half_side,  half_side, -half_side, 0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
         half_side, -half_side, -half_side, 0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
         half_side,  half_side, -half_side, 0.0f, 0.0f, -1.0f,  1.0f, 1.0f,

        // Bottom Face
        -half_side, -half_side,  half_side, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,         // (16)
        -half_side, -half_side, -half_side, 0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         half_side, -half_side,  half_side, 0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
         half_side, -half_side, -half_side, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,

        // Left Face
        -half_side,  half_side,  half_side, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,         // (20)
        -half_side,  half_side, -half_side, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -half_side, -half_side,  half_side, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -half_side, -half_side, -half_side, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f

    };

    // unsigned int indices[] = {
    //     0, 1, 2,   1, 2, 3, // Front Face
    //     3, 2, 6,   3, 7, 6, // Right Face
    //     4, 5, 6,   5, 6, 7, // Back Face
    //     1, 5, 4,   0, 1, 4, // Left Face
    //     1, 3, 5,   3, 5, 7, // Top Face
    //     0, 2, 4,   2, 4, 6  // Bottom Face
    // };
    unsigned int nIndices[] = {
        0,  1,  3,     0,  2,  3,
        4,  5,  6,     5,  6,  7,
        8,  9,  10,    9, 10, 11,
        12, 13, 15,   12, 14, 15,
        16, 17, 18,   17, 18, 19,
        20, 21, 22,   21, 22, 23
    };

    vao.init_VBO(nVertices, sizeof(nVertices)/sizeof(float), 0, 3, 8, 0);
    vao.set_vertex_attrib_pointer(nVertices, sizeof(nVertices)/sizeof(float), 1, 3, 8, 3);
    vao.set_vertex_attrib_pointer(nVertices, sizeof(nVertices)/sizeof(float), 2, 2, 8, 6);
    vao.init_EBO(nIndices, 36);
    position = glm::vec3(0, 0, 0);
    CollisionBox.center = position;
}   

void Cube::applyGravity(float dt)
{
    velocity.y += Gravity()*dt;
    position.y += velocity.y * abs(dt);
    //std::printf("Y Pos: %.2f", position.y);
    model = glm::translate(glm::mat4(1.0f), position);
    CollisionBox.center = position;
}

void Cube::move(float dx, float dy, float dz, float dt)
{
    if (dx > 0) pushing_right = true;
    if (dx < 0) pushing_left = true;
    force.x += dx * dt * 50; 
    force.z += dz * dt * 50; 
    
}

void Cube::update_horizontal_movement(float dt)
{ 
    if (force.x < 0 && !pushing_left) force.x = 0;
    if (force.x > 0 && !pushing_right) force.x = 0;

    if (velocity.x > 0) // If velocity is positive
        kinetic_force = mass * normal * friction_coefficient;

    else if (velocity.x < 0)
        kinetic_force = mass * normal * friction_coefficient * -1;
    
    std::printf("Kinetic Force: %.2f ", kinetic_force);
    if (force.x >= 700) force.x = 700; else if (force.x <= -700) force.x = -700; 
    if (abs( kinetic_force ) > abs(force.x)) kinetic_force = force.x * -1;
    float force_x = force.x + kinetic_force;
    std::printf("Force: %.2f ", force_x);
    acceleration.x = force_x / mass;
    
    velocity.x += acceleration.x * dt; if (velocity.x > 7) velocity.x = 7; else if (velocity.x < -7) velocity.x = -7;
    

    if (velocity.z > 0) // If Velocity is positive
        force.z -= mass * normal * friction_coefficient;

    if (velocity.z < 0)
        force.z += mass * normal * friction_coefficient;

    if (force.z >= 700) force.z = 700; else if (force.z <= -700) force.z = -700; // Cap the force to 700 or -700
    acceleration.z = force.z / mass;
    velocity.z += acceleration.z * dt; if (velocity.z > 7) velocity.z = 7; else if (velocity.z < -7) velocity.z = -7;
    

    position += glm::vec3(velocity.x * dt,  0, velocity.z * dt);
    model = glm::translate(model, position);
    update_collision_box();

}

void Cube::update_collision_box()
{   
    CollisionBox.center = position;
}

void Cube::bind_vao()
{
    vao.bind();
}