#include "cube.h"
#include <math.h>
#include <iostream>
Cube::Cube(float s_width) 
    //: //texture("Assets/container2.png")
{
    mass = 20; // (kilograms)
    normal = mass * Gravity();
    friction_coefficient = 0.05;
    max_velocity = 10;
    sideLength = s_width; // <-- Can you be less confusing?? Lol
    float half_side = sideLength/2;
    for (int i = 0; i < 3; i++)
        CollisionBox.r[i] = half_side; // Set all radii to half_side 
    
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
    if (dz > 0) pushing_down = true;
    if (dz < 0) pushing_up = true;

    force.x += dx * dt * 120; 
    force.z += dz * dt * 120; 
    // Note: force.(a) is the force applied to the cube in the respective direction
    //       force_a is the actual force being applied once the static kinetic friction has been overcome, which produces an acceleration
}

void Cube::update_horizontal_movement(float dt)
{ 
    if (force.x < 0 && !pushing_left) force.x = 0;
    if (force.x > 0 && !pushing_right) force.x = 0;

    if (velocity.x > 0) // If velocity is positive (Note that gravity is negative, so kinetic_force is already going against our velocity)
        kinetic_force[0] = mass * normal * friction_coefficient; // Kinetic force is force applied against our velocity

    else if (velocity.x < 0)
        kinetic_force[0] = mass * normal * friction_coefficient * -1;

    else kinetic_force[0] = 0;
    std::printf("Kinetic Force(X): %.2f ", kinetic_force[0]);

    if (force.x >= 700) force.x = 700; else if (force.x <= -700) force.x = -700; 

    // force_x represents the force being applied after the static friction has been surpassed. Thus, force_x will subtract itself, which will be 0 until force.x is greater than the
    // static friction force
    float force_x = force.x - (std::min(abs(kinetic_force[0]), abs(force.x))) * get_sign(force.x);

    // If there is no force being applied on the cube (No input), but the cube is moving, then the net force applied will be equal to the kinetic friction. This 
    // means that the force will be applied against our velocity, causing a gradual deceleration to simulate friction;
    if (force.x == 0 && velocity.x != 0)
        force_x = kinetic_force[0];

    std::printf("Force(X): %.2f ", force_x);
    acceleration.x = force_x / mass; // Using the resulting force, calculate the acceleration

    // Increment velocity using velocity acceleration kinematic equation
    velocity.x += acceleration.x * dt; 
    // Cap the velocity to max_velocity value
    if (velocity.x > max_velocity) velocity.x = max_velocity; else if (velocity.x < -max_velocity) velocity.x = -max_velocity;

    // If velocity falls betwen this range, then halt movement completely to avoid velocity oscillating from positive to negative
    if (velocity.x <= 0.25 && velocity.x >= -0.25) velocity.x = 0;

    position += glm::vec3(velocity.x * dt,  0, 0);
    model = glm::translate(model, position);
    update_collision_box();

}

void Cube::update_vertical_movement(float dt)
{
    if (force.z < 0 && !pushing_up) force.z = 0;
    if (force.z > 0 && !pushing_down) force.z = 0;

    if (velocity.z > 0) 
        kinetic_force[1] = mass * normal * friction_coefficient;   // Kinetic force is force applied against our velocity
    else if (velocity.z < 0)
        kinetic_force[1] = mass * normal * friction_coefficient * -1;
    else 
        kinetic_force[1] = 0;

    std::printf("Kinetic Force(Z): %.2f ", kinetic_force[1]);

    if (force.z >= 700) force.z = 700; else if (force.z <= -700) force.z = -700;
    float force_z = force.z - (std::min(abs(kinetic_force[1]), abs(force.z))) * get_sign(force_z);

    if (force.z == 0 && velocity.z != 0)
        force_z = kinetic_force[1];
    std::printf("Force(Z): %.2f ", force_z);

    acceleration.z = force_z / mass;

    velocity.z += acceleration.z * dt;
    
    // Clamp maximum velocity value
    if (velocity.z > max_velocity) velocity.z = max_velocity; else if (velocity.z < -max_velocity) velocity.z = -max_velocity;

    // If velocity falls betwen this range, then halt movement completely to avoid velocity oscillating from positive to negative
    if (velocity.z <= 0.25 && velocity.z >= -0.25) velocity.z = 0;

    
    position += glm::vec3(0,  0, velocity.z * dt);
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