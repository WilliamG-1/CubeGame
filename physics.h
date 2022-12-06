#pragma once
#include "glm/gtc/matrix_transform.hpp"
class Physics
{
public:
    virtual void applyGravity(float dt) = 0;
    float Gravity() { return gravity;}

protected:
    float velocity = 0;
    float x;
    float y;
    float xVelocity = 0;
    float yVelocity = 0;
    float mass = 0;

private:
    float gravity = -9.8f;
};
