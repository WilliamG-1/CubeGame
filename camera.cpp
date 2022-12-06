#include "camera.h"
#include <iostream>
#include <math.h>
// Perspective Camera
PerspectiveCamera::PerspectiveCamera(float fov, float screen_width, float screen_height, float near, float far)
    :
    projection(1.0f), view(1.0f), projectionView(1.0f)
{
    position = glm::vec3(0, 5, 40);
    focus = glm::vec3(0.0f, 0.0f, 0.0f);

    euler_angle(phi, theta); // Starting angle (Straight forwards)

    projection = glm::perspective(glm::radians(fov), screen_width/screen_height, near, far);
    view = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));

    recalculate();
}

void PerspectiveCamera::euler_angle(float phi, float theta)
{
    float p = 1;
    // Assume length of vector is 1 (normalized) so rho (p) is going to be 1 
    // General equations  Here, open gl uses right hand system, but the y is up and the z is forwards
    // x = p * sin(phi) * cos(theta)
    // z = p * sin(phi) * sin(theta)
    // y = p * cos(phi)
    // For camera looking forwards, phi = pi/2 | theta = pi/2
    
    front.x = p * sin(glm::radians(phi)) * cos(glm::radians(theta));
    front.z = p * sin(glm::radians(phi)) * sin(glm::radians(theta));
    front.y = p * cos(glm::radians(phi));
    
    front = glm::normalize(front);

    // Negate values because the negative axis is "Forwards" in our coordinate system
    //front.x *= -1;
    //front.y *= -1;
    front.z *= -1;
    //std::printf("Direction: (%.2f, %.2f, %.2f)\n", front.x, front.y, front.z);
    updateBasis();

    view = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
    recalculate();
}

void PerspectiveCamera::panCamera(int phi_direction, int theta_direction, float dt)
{
    phi -= phi_direction * dt * pan_speed;
    if (phi < 1)
        phi = 1;
    if (phi > 179)
        phi = 179;
    theta -= theta_direction * dt * pan_speed;
    euler_angle(phi, theta);
}

void PerspectiveCamera::move(CameraDirection direction, float dt)
{
    switch (direction)
    {
    case CameraDirection::FORWARD:
        position += front * dt * velocity;
        break;
    case CameraDirection::BACKWARD: // Backward
        position -= front * dt * velocity;
        break;
    case CameraDirection::LEFT: // Backward
        position -= right * dt * velocity;
        break;
    case CameraDirection::RIGHT: // Backward
        position += right * dt * velocity;
        break;
    case CameraDirection::UP:
        position += glm::vec3(0.0f, 1.0f, 0.0f) * dt * velocity;
        break;
    case CameraDirection::DOWN:
        position -= glm::vec3(0.0f, 1.0f, 0.0f) * dt * velocity;
        break;
    }
    view = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
    recalculate();
}

void PerspectiveCamera::moveView(glm::vec3 position)
{
    this->position = front + position;
    view = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
    recalculate();
}
void PerspectiveCamera::recalculate()
{
    projectionView = projection * view;
}

void PerspectiveCamera::updateBasis()
{
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
   // std::printf("Right: (%.2f, %.2f, %.2f)\n", right.x, right.y, right.z);
}










// OrthoGrapic Camera
OrthographicCamera::OrthographicCamera(float screen_width, float screen_height)
    :
    projection(1.0f), view(1.0f), projectionView(1.0f)
{

    projection = glm::ortho(0.0f, screen_width, 0.0f, screen_height);
    recalculate();
}

void OrthographicCamera::moveView(glm::vec3 position)
{
    view = glm::inverse(glm::translate(glm::mat4(1.0f), position));
    recalculate();
}

void OrthographicCamera::recalculate()
{
    projectionView = projection * view;
}