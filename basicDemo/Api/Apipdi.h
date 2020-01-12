#include "../define.h"
#include "Gpu/mainGPU.h"

GPU *mainGpu;

void initApipdi(){

    mainGpu = new GPU();

    if(mainGpu){

        //return true;

    }else{

        //return false;

    }
}

unsigned char* negativeImage( int width,  int height,  int channels, unsigned char* data , bool GPU){

     return mainGpu->negativeImage(width,height,channels,data);

}

unsigned char* grayScaleImage(int width, int height, int channels, unsigned char* data, bool GPU) {

    return mainGpu->grayScaleImage(width, height, channels, data);

}