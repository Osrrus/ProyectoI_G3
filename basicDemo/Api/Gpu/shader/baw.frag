#version 330 core

out vec4 FragColor;

uniform sampler2D text;

in vec2 uvs;


void main()
{
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

    float bin = 1.0f;
    if(luminance < umbral){
        bin = 0.0f;
    }
    
    result =vec4(vec3(bin), 1.0f);

    FragColor = result;

}