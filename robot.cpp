#include "robot.hpp"


/**function for determining if pixels are red*/
int getRedPixels(int row, int column){
	int r = get_pixel(cameraView, row, column, 0);
	int g = get_pixel(cameraView, row, column, 1);
	int b = get_pixel(cameraView, row, column, 2);
	int all = r+g+b;
	float redness = r/all;
	if (redness<1){
		return 0;
	}
	return redness;
}

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
	return -1;//returns -1 if no white pixels in row being checked
}
	}
	

/**function that returns true if every pixel in a given row is red
 */
bool allRed(int row){
	for (int column = 0; column<150; column++){
		if (getRedPixels(row, column)==0){
			return false;
		}
	}
	return true;
}

/**function that returns the diffeerence between where the red line is and where we want it to be */
int redError(int column){
	for (int row = 25; row<100; row++){
		//std::cout<<getRedPixels(row, column);
		if (getRedPixels(row, column)==0){
			return row;
		}
	}
	std::cout<<std::endl;
	return -1;
}

/**function for returning how far down is line from top when on side*/
double sideError(int column){
	int min = 25;
	for (int row = 0; row<100; row++){
		//std::cout<<getWhitePixels(row, column);
		if (getWhitePixels(row, column)==1){
			if (row<min){
				return min;
			}
			else{
			return row;
		}
		}
	}
	return -1;
}


int main(){
	bool sideLine = false;//changes to true when line detected on sides closer to robot, changes back to false when no line is detected
	bool rightTurn = true;//sets to false when a left turn is picked up so it doesn't turn back to the previous line being followed when that ends
	//up on the right of the image, sets back to true once no line detected on left
	double sideKP = 0.2;
	double frontKP = 0.07;
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	} 
    double vLeft;
    double vRight;
    while(1){
		if (sideError(0)>=70.0||sideError(149)>=70.0){
			sideLine=true;
		}
		if (sideError(0)==-1&&(sideError(149)==-1||!rightTurn)){
			sideLine=false;
		}
      takePicture();
      if (!sideLine&&findError()!=-1){
	  vRight=40.0-findError()*frontKP;
      vLeft=40.0+findError()*frontKP;
  }
   else {
	   if (sideError(0)==-1){
		   rightTurn=true;
	   }
	   if (sideError(0)>0&&sideError(149)==-1){
		   rightTurn=false;
		   vRight=20.0+sideError(0)*sideKP;
		   vLeft=20.0-sideError(0)*sideKP;
	   }
	   else if (sideError(149)>0&&rightTurn){
		   vRight=20.0-sideError(149)*sideKP;
		  vLeft=20.0+sideError(149)*sideKP;
	   }
  }
      setMotors(vLeft,vRight);
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
