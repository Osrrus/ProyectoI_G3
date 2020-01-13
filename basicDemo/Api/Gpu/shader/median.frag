#version 330 core
out vec4 FragColor;

uniform sampler2D text;
uniform vec2 kernel;

in vec2 uvs;

vec3 mediana(vec3 image)
{
	vec3 result;
    //const ivec2 kernel= ivec2(7,7);
	int nums=int(kernel.x)*int(kernel.y);

	vec3 colors[49];
	ivec2 ires = textureSize( text, 0 );
	float ResS = float( ires.s );
    float ResT = float( ires.t );
	int middleT = int(kernel.x)/2; 
	int middleS = int(kernel.y)/2;
	
	//Se tomar� como pivote el kernel.x/2 y el kernel.y/2
	//vec2(x,y)
    vec2 widthStep = vec2((1./ResS), 0.);
	vec2 heightStep = vec2(0. , (1./ResT));
	vec2 texel = uvs;
	//Maximos
	int top = middleT;
	int left = middleS;
	
	vec3 sum = vec3(0.0, 0.0, 0.0);
	int pos = 0;
	//Pasar colores del kernel a un arreglo
	for(int ii=0; ii < kernel.y; ii++)
	{
		texel = texel + (heightStep * (top - ii));
		texel = texel - (widthStep * left);
		
		for(int jj=0; jj < kernel.x; jj++)
		{
			vec3 textureAct = texture(text, texel).rgb;

			colors[pos] = textureAct;
			pos++;
			texel = texel + widthStep;
		}
		texel = uvs;
	}
	//Sort
	int n = nums;
	int newn;
	do{
		newn = 0;
		for (int j = 0; j < n-1; j++){
			if (colors[j].r > colors[j+1].r 
			&& colors[j].b > colors[j+1].b 
			&& colors[j].g > colors[j+1].g)
			{
				vec3 temp = colors[j];
				colors[j] = colors[j+1];
				colors[j+1] = temp;
				newn=j;
			}
		}
		n= newn;
				
	}while(n>0);

	//La mediana es el n�mero que est� 
	//en medio del conjunto ya ordenado
	int medio = int(ceil( nums/2.0 ));

	result = colors[medio];
	return result;
}

void main()
{
	
	vec3 image = texture2D(text, uvs).rgb;
	vec4 result;
	float umbral = 0.4f;
	const vec3 W = vec3( 0.2125, 0.7154, 0.0721 );
	float luminance = dot( image, W );

	result = vec4(mediana(image), 1.0f);

    FragColor = result;

}