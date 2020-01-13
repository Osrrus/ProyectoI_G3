#version 330 core

out vec4 FragColor;

uniform sampler2D text;
uniform vec2 kernel;

in vec2 uvs;

// sirve para los casos imparximpar iguales
vec3 gradientWithFor(vec3 image){
	vec3 result;
	ivec2 ires = textureSize( text, 0 );
	float ResS = float( ires.s );
    float ResT = float( ires.t );
    //ivec2 kernel = ivec2(3,3);
	int middleT = int(kernel.x)/2; 
	int middleS = int(kernel.y)/2;
	
	
	//Se tomar� como pivote el kernel.x/2 y el kernel.y/2
	//vec2(x,y)
    vec2 widthStep = vec2((1./ResS), 0. );
	vec2 heightStep = vec2(0. , (1./ResT));
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float dx = 0;
	float dy = 0;
	vec2 texel = uvs;
	//Maximos
	int top = middleT;
	int left = middleS;

	float midValue;
	float leftRightValue;

	midValue = 1;
	leftRightValue = 1;
	
	//Calculo de dy
	//Esquina superior maxima
	int midS = 1;
	for(int ii=0; ii < int(kernel.x); ii++)
	{
		texel = texel + (heightStep * (top - ii));
		texel = texel - (widthStep * left);
		
		if(ii == middleT) midS = 0;
		if(ii > middleT) midS = -1;
		for(int jj=0; jj < int(kernel.y); jj++)
		{
			float textureAct = dot( texture(text, texel).rgb, W );
	
			if(jj < middleS)
			{
				dx = dx - textureAct * (midS == 0 ? midValue : leftRightValue);
				dy = dy - textureAct * leftRightValue * midS;
			}else if(jj > middleS)
			{
				dx = dx + textureAct * (midS == 0 ? midValue : leftRightValue);
				dy = dy - textureAct * leftRightValue * midS;
			}
			else
			{
				dy = dy - textureAct * midValue * midS;
			}
			texel = texel + widthStep;
		}
		midS = 1;
		texel = uvs;
	}
	float magnitude = length( vec2( dx, dy ) );//Distance of two points
    vec3 target;
	//abs value of x's derivative
	//target = vec3( abs(dx), abs(dx), abs(dx) );
	//abs value of y's derivative
    //target = vec3( abs(dy), abs(dy), abs(dy) );
	//magnitude of derivates
    target = vec3( magnitude, magnitude, magnitude );
    result = mix( image, target, 1.0f );
	//1result = vec3(kernel.x,kernel.y, 1.0);
	return result;
}


void main()
{
	
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

	//	5 prewitt
    result = vec4(gradientWithFor(image), 1.0f);

    FragColor = result;

}