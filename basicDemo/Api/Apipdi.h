#include "../define.h"
#include "Gpu/mainGPU.h"
#include "Cpu/mainCPU.h"

GPU *mainGpu;

void initApipdi(){

    mainGpu = new GPU();

}

unsigned char* negativeImage( int width,  int height,  int channels, unsigned char* data , bool GPU){


     if(GPU){

        return mainGpu->negativeImage(width,height,channels,data);

    }else{

        return negativeImageCPU(width,height,channels,data);
    }

}

unsigned char* grayScaleImage(int width, int height, int channels, unsigned char* data, bool GPU) {

    if(GPU){

        return mainGpu->grayScaleImage(width, height, channels, data);

    }else{

        return grayScaleImageCPU(width,height,channels,data);
    }

}

unsigned char* robertsImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->robertsImage(width, height, channels, data, kernel);

}

unsigned char* avgImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->avgImage(width, height, channels, data, kernel);

}


unsigned char* toonImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->toonImage(width, height, channels, data, kernel);

}

unsigned char* medianImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->medianImage(width, height, channels, data, kernel);

}

unsigned char* lOfGuusImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->lOfGuusImage(width, height, channels, data, kernel);

}

unsigned char* blackWhiteImage(int width, int height, int channels, unsigned char* data, bool GPU) {

    return mainGpu->blackWhiteImage(width, height, channels, data);

}

unsigned char* prewittImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->prewittImage(width, height, channels, data, kernel);

}

unsigned char* sobelImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->sobelImage(width, height, channels, data, kernel);

}