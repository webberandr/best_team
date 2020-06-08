#include "robot.hpp"


int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 3.0;
    double vRight = 3.0;
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
      takePicture();
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
