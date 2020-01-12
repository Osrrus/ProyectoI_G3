#version 330 core

out vec4 FragColor;

uniform sampler2D text;
uniform vec2 kernel;
in vec2 uvs;

vec3 promedio(vec3 image)
{
	vec3 result;
	ivec2 ires = textureSize( text, 0 );
	float ResS = float( ires.s );
    float ResT = float( ires.t );
	int middleT = int(kernel.x)/2; 
	int middleS = int(kernel.y)/2;
	
	//Se tomar� como pivote el kernel.x/2 y el kernel.y/2
	//vec2(x,y)
    vec2 widthStep = vec2((1./ResS), 0. );
	vec2 heightStep = vec2(0. , (1./ResT));
	
	vec2 texel = uvs;
	//Maximos
	int top = middleT;
	int bottom = int (kernel.y) % 2 == 0 ? middleT - 1 : middleT;
	int left = middleS;
	int right =  int (kernel.x) % 2 == 0 ? middleS - 1 : middleS;

	vec3 sum = vec3(0.0, 0.0, 0.0);
	for(int ii=0; ii < kernel.y; ii++)
	{
		texel = texel + (heightStep * (top - ii));
		texel = texel - (widthStep * left);
		
		for(int jj=0; jj < kernel.x; jj++)
		{
			vec3 textureAct = texture(text, texel).rgb;
			sum = sum + textureAct;
			texel = texel + widthStep;
		}
		texel = uvs;
	}
	result = (1./ float (kernel.x*kernel.y)) * sum;
	return result;
}

void main()
{
	
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

	result = vec4(promedio(image), 1.0f);

    FragColor = result;

}