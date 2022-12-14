#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
class Shader
{
public:
    Shader();
    ~Shader();
    void bind();
    void init_shaders(const std::string& vertex_file_path, const std::string& fragment_file_path);
    void use_shader();

    void setUniform1i(const char* uniformName, int value);
    void setUniform1f(const char* uniformName, float value);
    void setUniformVec3fv(const char* uniformName, glm::vec3 vector);
    void setUniformVec3f(const char* uniformName, float x, float y, float z);
    void setUniformVec4fv(const char* uniformName, glm::vec4 vector);
    void setUniformVec4f(const char* uniformName, float v1, float v2, float v3, float v4);
    void setUniformMat4f(const char* uniformName, glm::mat4 matrix);
private:
    unsigned int program = 0;
    unsigned int vertex_shader = 0;
    unsigned int fragment_shader = 0;

    std::string read_shader_to_string(const std::string& file_path);
    void init_vertex( const std::string& path);
    void init_fragment( const std::string& path);
    void checkError(unsigned int shader);
    
};