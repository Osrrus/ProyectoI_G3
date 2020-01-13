
#pragma once

#include <string>
#include <iostream>


unsigned char * grayScaleImageCPU(int width, int height, int channels, unsigned char* data){

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    double r,g,b;
    unsigned char gray;
    width *=3;

    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {

            r = (double)data[(i*width + j) + 2] * 0.299;
            g = (double)data[(i*width + j) + 1] * 0.587;
            b = (double)data[(i*width + j) + 0] * 0.144;

            gray = floor((r + g + b + 0.5));

            imageData[i* width + j] = gray;
        }
    }

    return imageData;
}

unsigned char* negativeImageCPU(int width, int height, int channels, unsigned char* data) {

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    double r, g, b;
    unsigned char negative;
    width *= 3;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            r = 1.0 - (double)data[(i * width + j) + 2];
            g = 1.0 - (double)data[(i * width + j) + 1];
            b = 1.0 - (double)data[(i * width + j) + 0];

            negative = floor((r + g + b + 0.5));

            imageData[i * width + j] = negative;
        }
    }

    return imageData;
}