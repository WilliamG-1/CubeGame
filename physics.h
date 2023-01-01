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

    void cancel_x_velocity() { velocity.x = 0; }
    void cancel_y_velocity() { velocity.y = 0; }
    void cancel_z_velocity() { velocity.z = 0; }
    glm::vec3 get_velocity() const { return velocity; }

    float Gravity() { return gravity;}
protected:
    glm::vec3 velocity = {0, 0, 0};
    float x;
    float y;
    float z;
    float mass = 0;

private:
    float gravity = -9.8f;
};
