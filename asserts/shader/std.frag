#version 430 core
out vec4 FragColor;

layout (location = 0) uniform vec4 u_color;

void main()
{
   FragColor = u_color;
};