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
        Obj* plane;
        unsigned int frameBufferTexture,bufferTexture;
        unsigned int bufferWidth;
        unsigned int bufferHeight;
        
    public:
        GPU();
        ~GPU();
        unsigned char* negativeImage(int, int, int, unsigned char*);
        unsigned char* grayScaleImage(int, int, int, unsigned char*);
        unsigned char* robertsImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* avgImage(int, int, int, unsigned char*, glm::vec2);
        unsigned char* toonImage(int, int, int, unsigned char*, glm::vec2);
        void createTexture(unsigned int&, int, int, int, unsigned char*);
        bool createFrameBuffer(int , int);
};

