#include "robot.hpp"

int getWhitePixels(int row, int column){
	int white;
	int pix=get_pixel(cameraView, row, column, 3);
	if (pix>=250){
		white=1;
	}
	else {
		white=0;
	}
	return white;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 3.0;
    double vRight = 3.0;
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
      takePicture();
      //checkWhitePixels();
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
