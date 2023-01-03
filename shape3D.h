#pragma once
#include <glm/glm.hpp>
#include "vertexArrayObject.h"

class Shape3D
{
public:
    Shape3D();
    virtual float get_number_of_indices() const = 0;
    virtual void bind_vao() = 0;
    virtual void update_collision_box() = 0;

    glm::mat4& get_model_matrix() {return model;}
    glm::vec3& get_position_vector() {return position;}

protected:
    VertexArrayObject vao;
    glm::mat4 model;
    glm::vec3 position;
};