#version 330 core

in vec2 uvs;
out vec4 FragColor;

uniform sampler2D text;
uniform sampler1D textMat;
uniform vec2 kernel;

vec3 LoG(vec3 image){

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
	int kk = 0;
	for(int ii=0; ii < kernel.x; ii++)
	{
		texel = texel + (heightStep * (top - ii));
		texel = texel - (widthStep * left);
		
		for(int jj=0; jj < kernel.y; jj++)
		{
			vec3 textureAct = texture(text, texel).rgb;
			float LoGValue = texelFetch(textMat, kk, 0).r;
			sum = sum + textureAct * (LoGValue);
			texel = texel + widthStep; kk++;
		}
		texel = uvs;
	}

	result = vec3(sum);
	//result =image - result;
	return result;
}

void main()
{
	
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;

    result = vec4(LoG(image), 1.0f);

    FragColor = result;

}