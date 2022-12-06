#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::draw2D(Shader& shader, Shape2D& Shape2D)
{
    shader.use_shader();
    Shape2D.bind_vao();
    if(Shape2D.uses_ebo())
    {
        glDrawElements(GL_TRIANGLES, Shape2D.get_ebo_indices(), GL_UNSIGNED_INT, 0);
    }
}

void Renderer::draw3D(Shader& shader, Shape3D& shape, Material material)
{
    shader.use_shader();

    shader.setUniformMat4f("u_Model", shape.get_model_matrix());

    shader.setUniformVec3fv("u_Material.ambient", material.ambient);
    shader.setUniformVec3fv("u_Material.diffusion", material.diffusion);
    shader.setUniformVec3fv("u_Material.specular", material.specular);
    shader.setUniform1f("u_Material.shininess", material.shininess);

    shape.bind_vao();
    glDrawElements(GL_TRIANGLES, shape.get_number_of_indices(), GL_UNSIGNED_INT, 0);
}

void Renderer::draw3D(Shader& shader, Shape3D& shape, Color color)
{
    shader.setUniformVec4f("u_Color", color.r, color.g, color.b, color.a);

    shader.use_shader();
    shader.setUniformMat4f("u_Model", shape.get_model_matrix());

    shape.bind_vao();
    glDrawElements(GL_TRIANGLES, shape.get_number_of_indices(), GL_UNSIGNED_INT, 0);
}
