#version 330 core
// Atributte 0 of the vertex
layout (location = 0) in vec3 vertexPosition;

//layout (location = 1) in vec2 texture coordenate;
layout (location = 1) in vec2 textCoord;

//layout (location = 2) in vec3 normals;
layout (location = 2) in vec3 normals;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec2 uvs;

void main()
{
    uvs = textCoord;
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0f);
}