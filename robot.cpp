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

int getRedPixels(int row, int column){
	int red;
	int pix=get_pixel(cameraView, row, column, 3);
	if (pix>=250){
		red=1;
	}
	else {
		red=0;
	}
	return red;
}

/**function that finds difference between centre of line and centre of image
 * positive if right of line, negative if left of line
 * returns that value multiplied by kp.error
 */
double findError(){
	int row=30;
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
	double error = (centreWhite-75);//finds error with kp.error
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

/**function for returning how far down is line from top when on side*/
double sideError(int column){
	for (int row = 0; row<100; row++){
		//std::cout<<getWhitePixels(row, column);
		if (getWhitePixels(row, column)==1){
			return row;
		}
	}
	return 0;
}

int main(){
	double turnSpeed=20.0;
	double forward=40.0;
	bool sideLine = false;
	bool rightTurn = true;
	double sideKP = 0.2;
	double frontKP = 0.07;
	double turn = 50;
	int left = 40;
	int right = 110;
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	//double turn = 
    double vLeft;
    double vRight;
    //SavePPMFile("i0.ppm",cameraView);
    while(1){
		if (sideError(left)>=turn||sideError(right)>=turn){
			sideLine=true;
		}
		if (sideError(left)<=1&&sideError(right)<=1){
			sideLine=false;
		}
      takePicture();
      if (!sideLine){
	  vRight=forward-findError()*frontKP;
      vLeft=forward+findError()*frontKP;
  }
   else {
	   if (sideError(left)==0){
		   rightTurn=true;
	   }
	   if (sideError(left)>0&&sideError(right)==0){
		   rightTurn=false;
		   vRight=turnSpeed+sideError(left)*sideKP;
		   vLeft=turnSpeed-sideError(left)*sideKP;
	   }
	   else if (sideError(right)>0&&rightTurn){
		   vRight=turnSpeed-sideError(left)*sideKP;
		  vLeft=turnSpeed+sideError(right)*sideKP;
	   }
  }
      //checkWhitePixels();
      setMotors(vLeft,vRight);
     // std::cout<<"Error = "<<findError()<<" VPError= "<<vpError()<<std::endl;
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
      std::cout<<"RIght Error="<<sideError(right)<<std::endl;
       usleep(10000);
  } //while

} // main
