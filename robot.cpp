#include "robot.hpp"



int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
    double vLeft = 3.0;
    double vRight = 3.0;
    //SavePPMFile("i0.ppm",cameraView);
    int whiteArrayX[cameraView.width];
    int whiteArrayY[cameraView.height];
    while(1){
      takePicture();
      whiteSectorX = 0;
      whiteSectorY = 0;
      //checkWhitePixels();
      for (int y = 0; y <= cameraView.height; y++){
	for (int x = 0; x <= cameraView.width; x++){
	  int getWhitePixels(){
	int white;
	int pix=get_pixel(cameraView, x, y, 3);
	if (pix>=250){
		white=1;
	}
	else {
		white=0;
	}
		  
	
	  if(whiteArrayx[x]==1){
	    whiteSectorX = x;
	    break;
	  }
	
	return white;
	whiteArray[y]=white;
}  
	//width of the fov of the camera has been set to 150, so divide ppm image to 10 15 pixel sectors
	    
      }
      if(whiteSectorX < 15){
	      vLeft = 25;
	      vRight = 35;
      }
      if((whiteSectorX > 15) && (whiteSectorX < 30)){
	      vLeft = 25;
	      vRight = 33;
      }
      if((whiteSectorX > 30) && (whiteSectorX < 45)){
	      vLeft = 25;
	      vRight = 31;
      }
      if((whiteSectorX > 45) && (whiteSectorX < 60)){
	      vLeft = 25;
	      vRight = 29;
      }
      if((whiteSectorX > 60) && (whiteSectorX < 75)){
	      vLeft = 30;
	      vRight = 30;
      }
      if((whiteSectorX > 75) && (whiteSectorX < 90)){
	      vLeft = 30;
	      vRight = 30;
      }
      if((whiteSectorX > 90) && (whiteSectorX < 105)){
	      vLeft = 29;
	      vRight = 25;
      }
      if((whiteSectorX > 105) && (whiteSectorX < 120)){
	      vLeft = 31;
	      vRight = 25;
      }
      if((whiteSectorX > 120) && (whiteSectorX < 135)){
	      vLeft = 33;
	      vRight = 25;
      }
      if((whiteSectorX > 135) && (whiteSectorX < 150)){
	      vLeft = 35;
	      vRight = 25;
      }
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
