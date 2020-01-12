#include "../define.h"
#include "Gpu/mainGPU.h"

GPU *mainGpu;

void initApipdi(){

    mainGpu = new GPU();

}

unsigned char* negativeImage( int width,  int height,  int channels, unsigned char* data , bool GPU){

     return mainGpu->negativeImage(width,height,channels,data);

}

unsigned char* grayScaleImage(int width, int height, int channels, unsigned char* data, bool GPU) {

    return mainGpu->grayScaleImage(width, height, channels, data);

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