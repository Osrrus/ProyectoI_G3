
#pragma once
#define PI 3.1416

#include <string>
#include <iostream>


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
			gray = ((int)data[it + 0] * 0.2125) + ((int)data[it + 1] * 0.7154) + ((int)data[it + 2] * 0.0721);
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
	float res = sigma4 * (1 - sigma2) * expon;
	return res;
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
			//cout << kernelLoG[k] << ' ';

		}
	}

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
			for (int k = pivot.x + top; k <= pivot.x + bottom; k++)
			{
				for (int l = pivot.y + left; l <= pivot.y + right; l++)
				{
					if (k > -1 && l > -1 && k < height && l < width)
					{
						int it2 = (width * k + l) * channels;

						sum.x += (int)data[it2 + 0] * loGKernel[itKernel];
						sum.y += (int)data[it2 + 1] * loGKernel[itKernel];
						sum.z += (int)data[it2 + 2] * loGKernel[itKernel];
					}
					itKernel++;
				}
			}
			imageData[it + 0] = sum.x;
			imageData[it + 1] = sum.y;
			imageData[it + 2] = sum.z;
			sum = glm::vec3(0.0f);

		}
	}

	return imageData;
}