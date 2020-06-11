#include "robot.hpp"

/**function for deciding if a pixel is white or not
 * returns 1 if white, and 0 if not white
 */
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
/**function that finds difference between centre of line and centre of image
 * positive if right of line, negative if left of line
 * returns that value multiplied by kp.error
 */
double findError(){
	int row=0;
	double centreWhite;
	int firstWhite=-1;//initialising at value lower than lowest possible value for column
	int lastWhite=0;
	for (int column = 0; column<150; column++){
		if (firstWhite==-1&&getWhitePixels(row, column)==1){
		firstWhite=column;//only changed value of firstWhite in first instance of white
	}
	if (getWhitePixels(row, column)==1&&column>lastWhite){
		lastWhite=column;//finds last white
	}
	}
	centreWhite=((firstWhite+lastWhite)/2);//finds centre of white line
	double error = (centreWhite-75)*0.05;//finds error with kp.error
	if (firstWhite!=-1){
	return error;
}
else {
	return 0;//returns 0 if no white pixels in row being checked
}
	}

/**function that detects if line is in left or right column
 * call with 0 for letf column, call with 149 (or image.width-1) for right column
 * returns true if it finds any white pixels
 * ignores top quarter of image
 */
bool left_or_right(int column){
	for (int row = 25; row<100; row++){//starts at row 25
		if (getWhitePixels(row, column)==1){
			return true;
		}
	}
	return false;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	//double turn = 
    double vLeft;
    double vRight;
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
      takePicture();
      if (!left_or_right(149)&&!left_or_right(0)){
	  vRight=40.0-findError();
      vLeft=40.0+findError();
  }
   else if (left_or_right(0)){//turns left sharply if detects line in bottom 3/4 of left of image
		  vRight=40.0;
		  vLeft=10.0;
	  }
	else if (left_or_right(149)){//turns right sharply if detects line on right column of image, this one needs to take precedence for completion
		  vRight=10.0;
		  vLeft=40.0;
	  }
      //checkWhitePixels();
      setMotors(vLeft,vRight);
     // std::cout<<"Error = "<<findError()<<" VPError= "<<vpError()<<std::endl;
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
      std::cout<<" Error="<<findError()<<std::endl;
       usleep(10000);
  } //while

} // main
