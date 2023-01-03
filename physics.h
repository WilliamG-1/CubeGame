#pragma once
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>
struct AABBm
{
    glm::vec3 min; // Point denoting the "minimum"
    glm::vec3 max; // Point denoting the "maximum"
};
struct AABB
{
    glm::vec3 center;
    float r[3];
};

class Physics
{
public:
    virtual void applyGravity(float dt) = 0;
    // Simulate "Friction" so that object doesn't move forever
    virtual void update_horizontal_movement(float dt) = 0;
    
    void cancel_x_force() { force.x = 0; }
    void cancel_y_velocity() { velocity.y = 0; }
    void cancel_z_force() { force.z = 0; }
    virtual void not_applying_left_force() = 0;
    virtual void not_applying_right_force() = 0;

    glm::vec3 get_velocity() const { return velocity; }
    glm::vec3 get_acceleration() const { return acceleration; }
    glm::vec3 get_force() const { return force; }
    float Gravity() { return gravity;}
protected:
    glm::vec3 velocity = {0, 0, 0};
    glm::vec3 force = {0, 0, 0};
    glm::vec3 friction_force = {0, 0, 0};
    glm::vec3 acceleration = {0, 0, 0};
    float x;
    float y;
    float z;
    float mass = 0;
    float friction_coefficient = 0;
    float kinetic_force = 0;
    float normal = 0;
    bool pushing_left = false;
    bool pushing_right = false;
private:
    float gravity = -9.8f;
};
