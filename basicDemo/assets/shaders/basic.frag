#version 330 core

in vec2 uvs;
out vec4 FragColor;

uniform sampler2D texture1;
uniform int render;

void main()
{
    
    if(render == 1){
        vec4 tex = texture(texture1, uvs);
        tex.x = 1 - tex.x;
        tex.y = 1 - tex.y;
        tex.z = 1 - tex.z;
        FragColor = tex;

    }else if(render == 2){
        
        const vec3 w = vec3(0.2125, 0.7154, 0.0721);
        vec3 tex = texture(texture1, uvs).rgb;
        float bw = dot(tex,w);
        FragColor = vec4(bw,bw,bw,1.0);

    }else{

        FragColor = texture(texture1, uvs);
		//FragColor = vec4(uvs.x,uvs.y,0.0f,1.0f);

    }
}