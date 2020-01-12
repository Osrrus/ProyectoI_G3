#version 330 core

in vec2 uvs;
out vec4 FragColor;

uniform sampler2D texture1;
uniform int render;

void main()
{
    vec4 tex = texture(texture1, uvs);
    tex.x = 1 - tex.x;
    tex.y = 1 - tex.y;
    tex.z = 1 - tex.z;
    FragColor = tex;
    
}