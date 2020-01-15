#version 330 core

in vec3 inPosition;

void main()
{
    float x = inPosition.x;
    gl_Position = vec4(-1.0 + ((x + 1) * 0.0078125),0.0,0.0,1.0);
}