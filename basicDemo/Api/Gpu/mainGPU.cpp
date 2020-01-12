#include "mainGPU.h"

#define IMAGE_WIDTH 1024
#define IMAGE_HEIGHT 1024
#define IMG_NEGATIVE 0
#define IMG_GRAY_SCALE 1

GPU::GPU():
    viewDirection(0.0f, 0.0f, -1.0f),
    position(0.0f,0.0f,1.0f),
    UP(0.0f, 1.0f, 0.0f)
{
    
    bufferWidth =  IMAGE_WIDTH;
    bufferHeight = IMAGE_HEIGHT;

    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/negative.frag"));
    shaders.push_back(new Shader("Api/Gpu/shader/basic.vert","Api/Gpu/shader/grayScale.frag"));

    model = glm::mat4(1.0f);

    plane = objLoader("assets/Objects/plane.obj");

}

GPU::~GPU()
{
    for(auto i = 0; i < 2; i++){
        delete shaders[i];
    }
}

unsigned char* GPU::negativeImage(int width, int height, int channels, unsigned char* data){

    unsigned int id;
    createFrameBuffer(width,height);
    
    if (data)
    {
        createTexture(id,width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &id);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_NEGATIVE]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,id);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &id);
    glDeleteFramebuffers(1, &frameBufferTexture);

    return imageData;
}

unsigned char* GPU::grayScaleImage( int width,  int height,  int channels, unsigned char* data){

    unsigned int id;
    createFrameBuffer(width,height);

    if (data)
    {
        createTexture(id,width,height,channels,data);
    }
    else
    {
        std::cout << "Error Texture creation failed "<< std::endl;
        glDeleteTextures(1, &id);
    }

    glBindFramebuffer(GL_FRAMEBUFFER,frameBufferTexture);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);

    shaders[IMG_GRAY_SCALE]->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,id);

    plane->Draw();

    unsigned char* imageData = (unsigned char*)malloc((int)(width * height * (channels)));
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glDeleteTextures(1, &id);
    glDeleteFramebuffers(1, &frameBufferTexture);

    return imageData;
}

void GPU::createTexture(unsigned int &id , int width,  int height,  int channels , unsigned char* data){

    // Gets the texture channel format
    glGenTextures(1, &id);
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
    glBindTexture(GL_TEXTURE_2D, id);
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

glm::mat4 GPU::getWorlToViewMatrix() const{

	return glm::lookAt(position,position + viewDirection, UP);

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

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        return true;
    }

    return false;
}