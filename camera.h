#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection
{
    FORWARD = 0,
    BACKWARD = 1,
    LEFT = 2,
    RIGHT = 3,
    UP = 4,
    DOWN = 5
};

class PerspectiveCamera
{
public:
    PerspectiveCamera(float fov, float screen_width, float screen_height, float near, float far);

    void euler_angle(float phi, float theta);
    void move(CameraDirection direction, float dt);
    void updateBasis();
    void moveView(glm::vec3 position);
    void recalculate();
    void panCamera(int phi_direction, int theta_direction, float dt);

    glm::vec3 get_position() const {return position;}
    glm::vec3 get_front() const {return front;}
    glm::vec3 get_focus() const {return position + front;}
    glm::mat4 get_projection_view_matrix() {return projectionView;}
private:
    float velocity = 10;    // Camera speed
    float pan_speed = 90;   
    float phi = 90;
    float theta = 90;

    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 projectionView;

    glm::vec3 front;        // Direction vector pointing towards our scene (in front of camera)
    glm::vec3 position;     // Position of our camera
    glm::vec3 focus;        // Position that our camera is lookint at
    glm::vec3 right;        // Vector denoting our right axis
    glm::vec3 up;
};


class OrthographicCamera
{
public:
    OrthographicCamera(float screen_width, float screen_height);
    void moveView(glm::vec3 position);
    void recalculate();

    glm::mat4 get_projection_view_matrix() {return projectionView;}
private:
    glm::mat4 projectionView;
    glm::mat4 view;
    glm::mat4 projection;
};
