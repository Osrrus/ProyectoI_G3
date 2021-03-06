
#pragma once
#define PI 3.1416

#include<stdio.h>
#include<math.h>
#include <string>
#include <iostream>
#include <set>

const glm::vec3 W = glm::vec3(0.2125, 0.7154, 0.0721);

int uniqueColorsCPU(int width, int height, int channels, unsigned char* data){

	std::set<int> myset;
	int colors;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j)*3;

			colors = 0;
			colors += (int)data[it+0];
			colors *=100;
			colors += (int)data[it+1];
			colors *=100;
			colors += (int)data[it+2];

			if(!myset.count(colors)){

				myset.insert(colors);

			}
		}
	}

	return myset.size();
}

unsigned char * grayScaleImageCPU(int width, int height, int channels, unsigned char* data){

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    double rd,gd,bd;
    int gray;
    unsigned char* pixelOffset;
	int offset;
	/*
    for (int j = 0; j<height*width*channels; j+=3)
    {
            
		gray = ((int)data[j + 0] * 0.2125) + ((int)data[j + 1] * 0.7154) + ((int)data[j + 2] * 0.0721);
			
		imageData[j + 0] = gray;
		imageData[j + 1] = gray;
		imageData[j + 2] = gray;

    }*/

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j)*3;
			gray = ((int)data[it + 0] * W.x) + ((int)data[it + 1] * W.y) + ((int)data[it + 2] * W.z);
			imageData[it + 0] = gray;
			imageData[it + 1] = gray;
			imageData[it + 2] = gray;
		}
	}
    return imageData;
}

unsigned char* negativeImageCPU(int width, int height, int channels, unsigned char* data) {

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    int r, g, b;

	for (int j = 0; j < height*width*channels; j += 3)
	{

        r = (255-(int)data[j + 0]);
        imageData[j + 0] = r;
		r = (255-(int)data[j + 1]);
        imageData[j + 1] = r;
        r = (255-(int)data[j + 2]);
		imageData[j + 2] = r;

	}

    return imageData;
}

unsigned char* blackWhiteImageCPU(int width, int height, int channels, unsigned char* data) {

	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
	double bw,umbral = 60.0f;
	float r = 1.0f;

	for (int j = 0; j < height*width*channels; j += 3)
	{

		bw = ((double)data[j + 0] * 0.2125) + ((double)data[j + 1] * 0.7154) + ((double)data[j + 2] * 0.0721);

		if (bw < umbral) {
			imageData[j + 0] = 0.0f;
			imageData[j + 1] = 0.0f;
			imageData[j + 2] = 0.0f;
		}
		else {

			imageData[j + 0] = 255.0f;
			imageData[j + 1] = 255.0f;
			imageData[j + 2] = 255.0f;
		}

	}

	return imageData;
}

void initKernelValues(glm::vec2 kernel, int &middleR, int &middleC, float &top, float &bottom, float &left, float &right)
{
	middleR = int(kernel.x) / 2;
	middleC = int(kernel.y) / 2;

	top = -middleR;
	bottom = int(kernel.x) % 2 == 0 ? middleR - 1 : middleR;
	left = -middleC;
	right = int(kernel.y) % 2 == 0 ? middleC - 1 : middleC;

}

unsigned char* avgImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
	glm::vec3 sum = glm::vec3(0.0f);

	//Kernel
	int middleR, middleC;
	float top, bottom, left, right;
	
	initKernelValues(kernel, middleR, middleC, top, bottom, left, right);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j) * channels;
			glm::vec2 pivot = glm::vec2(i,j);
			int n = 0;
			//avg calculate
			for (int k = pivot.x+top; k <= pivot.x + bottom; k++)
			{
				for (int l = pivot.y+left; l <= pivot.y + right; l++)
				{
					if (k > -1 && l > -1 && k < height && l < width)
					{
						int it2 = (width * k + l) * channels;
						sum.x += (int)data[it2 + 0];
						sum.y += (int)data[it2 + 1];
						sum.z += (int)data[it2 + 2];
						n++;
					}
				}
			}
			imageData[it + 0] = (1./ float (n)) * sum.x;
			imageData[it + 1] = (1./ float (n)) * sum.y;
			imageData[it + 2] = (1./ float (n)) * sum.z;
			sum = glm::vec3(0.0f);

		}
	}
	
	return imageData;
}

float LoG(float x, float y, float sigma)
{
	float sigma4 = -(1 / (PI * sigma * sigma * sigma * sigma));
	float sigma2 = ((x * x + y * y) / (2 * sigma * sigma));
	float expon = exp(-sigma2);
	return sigma4 * (1 - sigma2) * expon;
}

std::vector<float> LoGKernel(float x, float y, float sigma)
{
	//init
	int minX, maxX;
	int minY, maxY;
	std::vector<float> kernelLoG;

	minX = (-x / 2);
	minX = minX + (int(x) % 2 == 0 ? 1 : 0);
	maxX = (x / 2);

	minY = (-y / 2);
	minY = minY + (int(y) % 2 == 0 ? 1 : 0);
	maxY = (y / 2);
	
	//calculate
	for (int i = maxX; i >= minX; i--)
	{
		for (int j = maxY; j >= minY; j--)
		{
			kernelLoG.push_back(LoG(i, j, sigma));	
		}
	}
	/*for (int i = 0; i < x*y; i++)
	{
		std::cout << kernelLoG[i] << ' ';

	}*/
	return kernelLoG;
}


unsigned char* lOfGuusImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));

	glm::vec3 sum = glm::vec3(0.0f);
	//Kernel
	int middleR, middleC;
	float top, bottom, left, right;

	initKernelValues(kernel, middleR, middleC, top, bottom, left, right);
	//Calculate Laplace or Gaussian matrix
	std::vector<float> loGKernel = LoGKernel(kernel.x, kernel.y, 1.0f);

	//Iterate in image
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j) * channels;
			glm::vec2 pivot = glm::vec2(i, j);
			int itKernel = 0;
			//LoG calculate
			for (int k = abs(pivot.x + top); k <= pivot.x + bottom; k++)
			{
				for (int l = abs(pivot.y + left); l <= pivot.y + right; l++)
				{
					if (k > -1 && l > -1 && k < height && l < width)
					{
						int it2 = (width * k + l) * channels;

						sum += glm::vec3((double)data[it2 + 0], (double)data[it2 + 1], (double)data[it2 + 2]) * loGKernel[itKernel];
					}
					//else {
					//	int finalK, finalL;
					//	finalK = k < 0 ? 0 : k;
					//	finalK = k >= height ? height - 1 : k;
					//	finalL = l < 0 ? 0 : l;
					//	finalL = l >= width ? width - 1 : l;
					//	//std::cout << "hi";
					//	int it2 = (width * finalK + finalL) * channels;

					//	sum += glm::vec3((double)data[it2 + 0], (double)data[it2 + 1], (double)data[it2 + 2]) * loGKernel[itKernel];
					//}
					itKernel++;
				}
			}
			sum.x = sum.x > 255 ? 255 : sum.x;
			sum.y = sum.y > 255 ? 255 : sum.y;
			sum.z = sum.z > 255 ? 255 : sum.z;

			sum.x = sum.x < 0 ? 0 : sum.x;
			sum.y = sum.y < 0 ? 0 : sum.y;
			sum.z = sum.z < 0 ? 0 : sum.z;
			imageData[it + 0] = sum.x;
			imageData[it + 1] = sum.y;
			imageData[it + 2] = sum.z;
			sum = glm::vec3(0.0f);

		}
	}

	return imageData;
}

std::vector<float> sobelKernelX(float x, float y) 
{
	std::vector<float> sobel;
	
	//init
	int minX, maxX;
	int minY, maxY;
	minX = (-x / 2);
	minX = minX + (int(x) % 2 == 0 ? 1 : 0);
	maxX = (x / 2);

	minY = (-y / 2);
	minY = minY + (int(y) % 2 == 0 ? 1 : 0);
	maxY = (y / 2);

	for (int i = maxX; i >= minX; i--)
	{
		for (int j = maxY; j >= minY; j--)
		{
			if (i*i+j*j != 0)
			{
				sobel.push_back(i / (float)(i * i + j * j));
			}
			else {
				sobel.push_back(0.0f);
			}
		}
		std::cout << std::endl;
	}
	return sobel;
}
std::vector<float> sobelKernelY(float x, float y)
{
	std::vector<float> sobel;
	//init
	int minX, maxX;
	int minY, maxY;
	minX = (-x / 2);
	minX = minX + (int(x) % 2 == 0 ? 1 : 0);
	maxX = (x / 2);

	minY = (-y / 2);
	minY = minY + (int(y) % 2 == 0 ? 1 : 0);
	maxY = (y / 2);

	for (int i = maxX; i >= minX; i--)
	{
		for (int j = maxY; j >= minY; j--)
		{
			if (i * i + j * j != 0)
			{
				sobel.push_back(j / (float)(i * i + j * j));
			}
			else {
				sobel.push_back(0.0f);
			}
		}
	}
	return sobel;
}
std::vector<float> prewittKernelY(float x, float y)
{
	std::vector<float> prewitt;
	//init
	int minX, maxX;
	int minY, maxY;
	minX = (-x / 2);
	minX = minX + (int(x) % 2 == 0 ? 1 : 0);
	maxX = (x / 2);

	minY = (-y / 2);
	minY = minY + (int(y) % 2 == 0 ? 1 : 0);
	maxY = (y / 2);

	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			prewitt.push_back(i);
		}
	}
	return prewitt;
}
std::vector<float> prewittKernelX(float x, float y)
{
	std::vector<float> prewitt;
	//init
	int minX, maxX;
	int minY, maxY;
	minX = (-x / 2);
	minX = minX + (int(x) % 2 == 0 ? 1 : 0);
	maxX = (x / 2);

	minY = (-y / 2);
	minY = minY + (int(y) % 2 == 0 ? 1 : 0);
	maxY = (y / 2);

	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			prewitt.push_back(j);
		}
	}
	return prewitt;
}

std::vector<float> robertsKernelX(float x, float y)
{
	std::vector<float> roberts;
	roberts.assign(int(x*y),0.0f);
	//init
	int N = int(x) < int(y) ? int(x) : int(y);

	N = N % 2 == 0 ? N : N - 1;
	int middle = N / 2;
	float peso = middle;

	int pos = 0;
	for (int i = 0; i < (N); i++)
	{
		roberts[pos] =peso;
		peso--;
		if (peso == 0) peso = -1;
		pos += N+1;
	}
	
	return roberts;
}

std::vector<float> robertsKernelY(float x, float y)
{
	std::vector<float> roberts;
	roberts.assign(int(x * y), 0.0f);
	//init
	int N = int(x) < int(y) ? int(x) : int(y);

	N = N % 2 == 0 ? N : N - 1;
	int middle = N / 2;
	float peso = -middle;

	int pos = 0;
	for (int i = 0; i < (N); i++)
	{
		roberts[pos] = peso;
		peso++;
		if (peso == 0) peso = 1;
		pos += N+1;
	}
	
	return roberts;
}

unsigned char* edgeImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel, std::vector<float> sobKernelX, std::vector<float> sobKernelY)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));

	//Kernel
	int middleR, middleC;
	float top, bottom, left, right;

	initKernelValues(kernel, middleR, middleC, top, bottom, left, right);
	//Calculate Sobel matrix
	float dx = 0.0f;
	float dy = 0.0f;
	//Iterate in image
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j) * channels;
			glm::vec2 pivot = glm::vec2(i, j);
			int itKernel = 0;
			//LoG calculate
			for (int k = abs(pivot.x + top); k <= pivot.x + bottom; k++)
			{
				for (int l = abs(pivot.y + left); l <= pivot.y + right; l++)
				{
					if (k < height && l < width)
					{
						int it2 = (width * k + l) * channels;

						float dataAct = ((int)data[it2 + 0] * W.x) + ((int)data[it2 + 1] * W.y) + ((int)data[it2 + 2] * W.z);
						dx += dataAct * sobKernelX[itKernel];
						dy += dataAct * sobKernelY[itKernel];

					itKernel++;
					}
				}
			}

			float magnitude = sqrt(dx * dx + dy * dy); //Distance of two points

			imageData[it + 0] = magnitude;
			imageData[it + 1] = magnitude;
			imageData[it + 2] = magnitude;
			dx = 0.0f;
			dy = 0.0f;
		}
	}

	return imageData;
}


unsigned char* sobelImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));

	//Calculate Sobel matrix
	std::vector<float> sobKernelX = sobelKernelX(kernel.x, kernel.y);
	std::vector<float> sobKernelY = sobelKernelY(kernel.x, kernel.y);
	imageData = edgeImageCPU(width, height, channels, data, kernel, sobKernelX, sobKernelY);
	return imageData;
}

unsigned char* prewittImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));

	//Calculate Prewit matrix
	std::vector<float> preKernelX = prewittKernelX(kernel.x, kernel.y);
	std::vector<float> preKernelY = prewittKernelY(kernel.x, kernel.y);
	
	imageData = edgeImageCPU(width, height, channels, data, kernel, preKernelX, preKernelY);
	return imageData;
}

unsigned char* robertsImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));

	//Calculate Sobel matrix
	std::vector<float> robKernelX = robertsKernelX(kernel.x, kernel.y);
	std::vector<float> robKernelY = robertsKernelY(kernel.x, kernel.y);

	imageData = edgeImageCPU(width, height, channels, data, kernel, robKernelX, robKernelY);
	return imageData;
}

unsigned char* medianImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
	glm::vec3 sum = glm::vec3(0.0f);
	std::vector<glm::vec3> colors;
	//Kernel
	int middleR, middleC;
	float top, bottom, left, right;

	initKernelValues(kernel, middleR, middleC, top, bottom, left, right);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int it = (width * i + j) * channels;
			glm::vec2 pivot = glm::vec2(i, j);
			//colors in vector
			for (int k = pivot.x + top; k <= pivot.x + bottom; k++)
			{
				for (int l = pivot.y + left; l <= pivot.y + right; l++)
				{
					if (k > -1 && l > -1 && k < height && l < width)
					{
						int it2 = (width * k + l) * channels;
						colors.push_back(glm::vec3((int)data[it2 + 0], (int)data[it2 + 1], (int)data[it2 + 2]));
					}
				}
			}
			// sort colors
			int n = colors.size();
			int newn;
			do {
				newn = 0;
				for (int j = 0; j < n - 1; j++) {
					if (colors[j].r > colors[j + 1].r
						&& colors[j].b > colors[j + 1].b
						&& colors[j].g > colors[j + 1].g)
					{
						glm::vec3 temp = colors[j];
						colors[j] = colors[j + 1];
						colors[j + 1] = temp;
						newn = j;
					}
				}
				n = newn;

			} while (n > 0);

			//La mediana es el n�mero que est� 
			//en medio del conjunto ya ordenado
			int medio = int(ceil(colors.size() / 2.0));

			
			imageData[it + 0] = colors[medio].x;
			imageData[it + 1] = colors[medio].y;
			imageData[it + 2] = colors[medio].z;
			colors.clear();
		}
	}

	return imageData;
}

unsigned char* toonImageCPU(int width, int height, int channels, unsigned char* data, glm::vec2 kernel)
{
	unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
	unsigned char* edges = (unsigned char*)malloc((int)(width * height * (channels)));
	edges = robertsImageCPU(width,height,channels,data,kernel);

	glm::vec3 sum = glm::vec3(0.0f);
	std::vector<glm::vec3> colors;
	//Kernel
	int middleR, middleC;
	float top, bottom, left, right;

	initKernelValues(kernel, middleR, middleC, top, bottom, left, right);
	glm::vec3 result(0.0f);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//quantization colors
			int it = (width * i + j) * 3;
			result.x = (int)data[it + 0];
			result.y = (int)data[it + 1];
			result.z = (int)data[it + 2];
			
			glm::vec3 stepSize = glm::vec3(10.0);
			result *= stepSize;

			result = round(result);

			result /= stepSize;
			result.x =result.x - edges[it + 0];
			result.y =result.y - edges[it + 1];
			result.z =result.z - edges[it + 2];

			result.x = result.x > 255 ? 255 : result.x;
			result.y = result.y > 255 ? 255 : result.y;
			result.z = result.z > 255 ? 255 : result.z;

			result.x = result.x < 0 ? 0 : result.x;
			result.y = result.y < 0 ? 0 : result.y;
			result.z = result.z < 0 ? 0 : result.z;

			imageData[it + 0] = result.x;
			imageData[it + 1] = result.y;
			imageData[it + 2] = result.z;
		}
	}
	return imageData;
}