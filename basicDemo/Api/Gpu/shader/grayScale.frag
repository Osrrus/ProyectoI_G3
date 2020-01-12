#version 330 core

in vec2 uvs;
out vec4 FragColor;

uniform sampler2D texture1;
uniform int render;

void main()
{
    
    const vec3 w = vec3(0.2125, 0.7154, 0.0721);
    vec3 tex = texture(texture1, uvs).rgb;
    float bw = dot(tex,w);
    FragColor = vec4(bw,bw,bw,1.0);

}