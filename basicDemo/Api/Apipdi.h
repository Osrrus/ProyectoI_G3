#include "../define.h"
#include "Gpu/mainGPU.h"
#include "Cpu/mainCPU.h"
  
GPU *mainGpu;
std::chrono::time_point<std::chrono::system_clock> start, end;
long time_exec;

void initApipdi(){

    mainGpu = new GPU();
    srand (time(NULL));
}

void getTime(){

    end = std::chrono::system_clock::now();
    time_exec = std::chrono::duration_cast<std::chrono::milliseconds>
                (end-start).count();
    std::cout <<time_exec<<std::endl;

}

void setTime(){

    start = std::chrono::system_clock::now();

}

unsigned char* negativeImage( int width,  int height,  int channels, unsigned char* data , bool GPU){

    setTime();

    if(GPU){

        return mainGpu->negativeImage(width,height,channels,data);

    }else{

        return negativeImageCPU(width,height,channels,data);
    }

    
    
}

unsigned char* grayScaleImage(int width, int height, int channels, unsigned char* data, bool GPU) {

    setTime();

    if(GPU){

        return mainGpu->grayScaleImage(width, height, channels, data);

    }else{

        return grayScaleImageCPU(width,height,channels,data);
    }

}

unsigned char* robertsImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->robertsImage(width, height, channels, data, kernel);


}

unsigned char* avgImage(int width, int height, int channels, unsigned char* data, bool GPU, glm::vec2 kernel) {

    setTime();

    if (GPU)
    {
        return mainGpu->avgImage(width, height, channels, data, kernel);
    }
    else {
        return avgImageCPU(width, height, channels, data, kernel);
    }

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

    setTime();

	if (GPU) {

		return mainGpu->blackWhiteImage(width, height, channels, data);

	}
	else {

		return blackWhiteImageCPU(width, height, channels, data);
		
	}
}

unsigned char* prewittImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->prewittImage(width, height, channels, data, kernel);

}

unsigned char* sobelImage(int width, int height, int channels, unsigned char* data, bool GPU , glm::vec2 kernel) {

    return mainGpu->sobelImage(width, height, channels, data, kernel);

}