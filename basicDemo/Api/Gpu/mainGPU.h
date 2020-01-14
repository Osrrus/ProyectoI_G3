#pragma once

#include <string>
#include <iostream>
#include "../define.h"
#include "../components/loader.h"
#include "../components/Obj.h"

//#define SHADER_NUMBER 2

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL


//extern const unsigned int ShaderNumber = SHADER_NUMBER;

class GPU
{
    private:

        std::vector<Shader*> shaders;
        std::vector<float> vectorKernel;
        Obj* plane;
        unsigned int frameBufferTexture,bufferTexture;
        unsigned int bufferWidth;
        unsigned int bufferHeight;
        unsigned int textureId,textureIdKernel;
        bool bufferinit;

    public:

        GPU();
        ~GPU();
        unsigned char* negativeImage(int, int, int, unsigned char*);
        unsigned char* grayScaleImage(int, int, int, unsigned char*);
        unsigned char* blackWhiteImage(int, int, int, unsigned char*);
        unsigned char* robertsImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* avgImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* toonImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* medianImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* lOfGuusImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* sobelImage(int, int , int , unsigned char*, glm::vec2);
        unsigned char* prewittImage(int, int , int , unsigned char*, glm::vec2);
        void createTexture(int, int, int, unsigned char*);
        void createTexture1D();
        void fillVectorOfKernell();
        bool createFrameBuffer(int , int);
};

