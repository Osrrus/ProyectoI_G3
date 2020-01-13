#version 330 core

out vec4 FragColor;

uniform sampler2D text;
uniform sampler1D textMat;

in vec2 coordText;

vec3 LoG(vec3 image){

	vec3 result;
	float vect = texture1D(textMat, 0).r;
	// floata = texelFetch
	result = vec3(vect+0.5);
	return result;
    
}

void main()
{
	
	vec3 image = texture2D(text, coordText).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

    result = vec4(LoG(image), 1.0f);

    FragColor = result;

}