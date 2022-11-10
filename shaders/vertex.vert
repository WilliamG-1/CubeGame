#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0f);
    FragPos = vec3(u_Model * vec4(aPos, 1.0f));
    Normal = aNormal;
}