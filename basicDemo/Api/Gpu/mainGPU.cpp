#include "mainGPU.h"

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080
#define IMG_NEGATIVE 0
#define IMG_GRAY_SCALE 1
#define IMG_ROBERTS 2
#define IMG_AVG 3
#define IMG_TOON 4
#define IMG_MEDIAN 5
#define IMG_LOFGAUS 6
#define IMG_BLACKWHITE 7
#define IMG_PREWITT 8
#define IMG_SOBEL 9

GPU::GPU(){
    
    bufferWidth =  IMAGE_WIDTH;
    bufferHeight = IMAGE_HEIGHT;

    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/negative.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/grayScale.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/roberts.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/avg.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/toon.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/median.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/lapofgaus.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/baw.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/prewitt.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/sobel.frag"));

    plane = objLoader("assets/Objects/plane.obj");

    glGenTextures(1, &bufferTexture);
    glGenTextures(1, &textureIdKernel);
}

GPU::~GPU()
{
    for(auto i = 0; i < 2; i++){
        delete shaders[i];
    }
}

unsigned char* GPU::negativeImage(int width, int height, int channels, unsigned char* data){

    createFrameBuffer(width,height);
    
    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_NEGATIVE]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::grayScaleImage( int width,  int height,  int channels, unsigned char* data){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_GRAY_SCALE]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::blackWhiteImage( int width,  int height,  int channels, unsigned char* data){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_BLACKWHITE]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::robertsImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){


    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_ROBERTS]->use();

    shaders[IMG_ROBERTS]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;

}

unsigned char* GPU::avgImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_AVG]->use();

    shaders[IMG_AVG]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;

}

unsigned char* GPU::toonImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_TOON]->use();

    shaders[IMG_TOON]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::medianImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_MEDIAN]->use();

    shaders[IMG_MEDIAN]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::lOfGuusImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    fillVectorOfKernell();
    createTexture1D();

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_LOFGAUS]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    shaders[IMG_LOFGAUS]->setInt("textMat", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_1D, textureIdKernel);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);
    glDeleteTextures(1,&textureIdKernel);

    return imageData;
}

unsigned char* GPU::prewittImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_PREWITT]->use();

    shaders[IMG_PREWITT]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

unsigned char* GPU::sobelImage(int width,  int height,  int channels, unsigned char* data , glm::vec2 kernel){

    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &textureId);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_SOBEL]->use();

    shaders[IMG_SOBEL]->setVec2("kernel",kernel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &textureId);
    glDeleteFramebuffers(1, &frameBufferTexture);
    glDeleteTextures(1,&bufferTexture);

    return imageData;
}

void GPU::createTexture(int width,  int height,  int channels , unsigned char* data){

    // Gets the texture channel format
    //glGenTextures(1, &textureId);
    GLenum format;
    switch (channels)
    {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
    }

    // Binds the texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    // Creates the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    // Creates the texture mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set the filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool GPU::createFrameBuffer( int width,  int height){

    glGenFramebuffers(1,&frameBufferTexture);
    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);

    glGenTextures(1,&bufferTexture);
    glBindTexture(GL_TEXTURE_2D,bufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,bufferTexture,0);

    GLenum buffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1,buffers);

    return false;
    
}

void GPU::createTexture1D(){

	//glGenTextures(1, &textureIdKernel);
	// Loads the texture
	int textureWidth, textureHeight, numberOfChannels;
	// Gets the texture channel format
	
	// Binds the texture
	glBindTexture(GL_TEXTURE_1D, textureIdKernel);
	// Creates the texture
	
	// Set the filtering parameters
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32F, 49, 0, GL_RED, GL_FLOAT, &vectorKernel[0]);
	glBindTexture(GL_TEXTURE_1D, 0);

}

void GPU::fillVectorOfKernell(){

    vectorKernel.clear();
    vectorKernel.assign(49, 0.6f);
}
