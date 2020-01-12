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
        glm::mat4 model;
        Obj* plane;
        const glm::vec3 UP;
        const glm::vec3 position;
        const glm::vec3 viewDirection;
        unsigned int frameBufferTexture,bufferTexture;
        unsigned int bufferWidth;
        unsigned int bufferHeight;
        
    public:
        GPU();
        ~GPU();
        unsigned char* negativeImage(int, int, int, unsigned char*);
        unsigned char* grayScaleImage(int, int, int, unsigned char*);
        void createTexture(unsigned int&, int, int, int, unsigned char*);
        glm::mat4 getWorlToViewMatrix() const;
        bool createFrameBuffer(int , int);
};

