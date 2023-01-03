#include "transformations.h"
#include <iostream>
#include <random>

// void Transformations::rotate2D(glm::mat4& model, Shape2D& shape, float width, float degrees)
// {
//     model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
//     model = glm::rotate(model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-shape.get_x() - width/2, -shape.get_y() - width/2, 0.0f));
// }

void Transformations::scale(glm::mat4& model, Shape2D& shape, float width, float scalar)
{
    model = glm::translate(glm::mat4(1.0f), glm::vec3(shape.get_x() + width/2, shape.get_y() + width/2, 0.0f));
    model = glm::scale(model, glm::vec3(scalar, scalar, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-(shape.get_x() + width/2), -(shape.get_y() + width/2), 0.0f));
}


void Transformations::translate3D(Shape3D& shape, float xTranslate, float yTranslate, float zTranslate)
{
    
    shape.get_model_matrix() = glm::translate(shape.get_model_matrix(), glm::vec3(xTranslate, yTranslate, zTranslate));
    shape.get_position_vector() += glm::vec3(xTranslate, yTranslate, zTranslate);
    shape.update_collision_box();
}

void Transformations::rotate3D(Shape3D& shape, float xRotation, float yRotation, float zRotation, glm::vec3 axes)
{
   
    shape.get_model_matrix() = glm::rotate(shape.get_model_matrix(), glm::radians(xRotation), glm::vec3(axes.x, 0.0f, 0.0f)) *  
            glm::rotate(glm::mat4(1.0f), glm::radians(yRotation), glm::vec3(0.0f, axes.y, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(zRotation), glm::vec3(0.0f, 0.0f, axes.z));
}

int Transformations::randint(int start, int end)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(start, end);
    return dist(rng);
}