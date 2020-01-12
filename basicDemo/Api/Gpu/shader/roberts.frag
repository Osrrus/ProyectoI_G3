#version 330 core
out vec4 FragColor;

uniform sampler2D text;
uniform vec2 kernel;
in vec2 uvs;

vec3 roberts(vec3 image)
{
	vec3 result;
	ivec2 ires = textureSize( text, 0 );
	float ResS = float( ires.s );
    float ResT = float( ires.t );
    //ivec2 kernel = ivec2(3,3);
	int middleT = int(kernel.x)/2; 
	int middleS = int(kernel.y)/2;
	
	
	//Se tomará como pivote el kernel.x/2 y el kernel.y/2
	//vec2(x,y)
    vec2 widthStep = vec2((1./ResS), 0. );
	vec2 heightStep = vec2(0. , (1./ResT));
	vec2 widthHeightStep = vec2((1./ResS), (1./ResT));
	vec2 widthNegativeHeightStep  = vec2((1./ResS), (-1./ResT));
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float textureCoord = dot( texture(text, uvs).rgb, W );

	float dx = 0;
	float dy = 0;
	vec2 texel = uvs;
	//Maximos
	int top = middleT;
	int bottom = int (kernel.x) % 2 == 0 ? middleT - 1 : middleT;
	int left = middleS;
	int right =  int (kernel.y) % 2 == 0 ? middleS - 1 : middleS;


	float midValue;
	float leftRightValue;
	//Maximos
	
	vec2 texelX=uvs, texelY=uvs;
	int N = int(kernel.x) < int(kernel.y) ? int(kernel.x) : int(kernel.y); 
	
	N = N % 2 == 0 ? N : N-1;
	int middle = N/2;
	float peso = middle;
	for(int ii=0; ii < N; ii++)
	{

		texelY = texelY + (widthHeightStep * (middle - ii));
		texelX = texelX - (widthNegativeHeightStep * (middle - ii));//revisar
	
		dx = dx + dot( texture(text, texelX).rgb, W ) * peso;
		dy = dy + dot( texture(text, texelY).rgb, W ) * peso;
		peso--;
		if(peso == 0) peso = -1;
		texelX = uvs;
		texelY = uvs;

	}

	float magnitude = length( vec2( dx, dy ) );//Distance of two points
    vec3 target;
    target = vec3( magnitude, magnitude, magnitude );
    result = mix( image, target, 1.0f );
	return result;
}

void main()
{
	
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

    result = vec4(roberts(image), 1.0f);
	
    FragColor = result;

}