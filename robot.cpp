#include "robot.hpp"


/**function for determining if pixels are red*/
int getRedPixels(int row, int column){
	int r = get_pixel(cameraView, row, column, 0);
	int g = get_pixel(cameraView, row, column, 1);
	int b = get_pixel(cameraView, row, column, 2);
	int all = r+g+b;
	if (all==0){
		return all;
	}
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
 * returns that value, works for both red pixels and white pixels depending on which maze is selected in user input
 */
double findError(int maze){
	int desPoint=75;//desired centre of white line
	int checkColumns=150;//checks all columns
	if (maze==2){
		desPoint=30;//desired centre of red line
		checkColumns=75;}//how many columns to check for challenge, want to hug left
	int row=75;
	double centreLine;
	int firstLine=-1;//initialising at value lower than lowest possible value for column, is first instance of 
	int lastLine=0;
	for (int column = 0; column<checkColumns; column++){
		if (maze==1){
		if (firstLine==-1&&getWhitePixels(row, column)==1){firstLine=column;}//only changed value of firstWhite in first instance of white
	if (getWhitePixels(row, column)==1&&column>lastLine){lastLine=column;}//finds last white
}
if (maze==2){
		if (firstLine==-1&&getRedPixels(row, column)==1){firstLine=column;}//only changed value of firstWhite in first instance of white
	if (getRedPixels(row, column)==1&&column>lastLine){lastLine=column;}//finds last white
}
	}
	centreLine=((firstLine+lastLine)/2);//finds centre of white/red line
	double error = (centreLine-desPoint);//finds error with kp.error
	if (firstLine!=-1){return error;}
else {return -1;}//returns -1 if no white/red pixels in row being checked
	}
	
	

/**returns true if row has at least 1 red pixel
 */
bool hasRed(int row){
	for (int column = 0; column<150; column++){
		if (getRedPixels(row, column)==1){
			return true;
		}
	}
	return false;
}

/**function that returns the diffeerence between where the red line is and where we want it to be */
int redError(int column){
	for (int row = 10; row<100; row++){
		//std::cout<<getRedPixels(row, column);
		if (getRedPixels(row, column)==1){
			return row;
		}
	}
	std::cout<<std::endl;
	return -1;
}

/**function for returning how far down is line from top when on side*/
double sideError(int column){
	int min = 10;
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

/**function for setting left speed in challenge*/
double challengeLeft(bool hasLeftLine, bool fullTurn, int maze, int count, double forward, double turnSpeed, double vLeft, double vRight){
	double frontKp=0.2;
	if (redError(149)!=-1&&hasLeftLine&&!fullTurn){
return turnSpeed+redError(149);
}
	if (fullTurn){
	if (count<10){//waits a bit before starting to turn so it doesn't hit the wall.
	return forward;
}
else{
	return turnSpeed-5;//starts to turn after a bit
}
}
return forward+findError(maze)*frontKp;
}

/**function for setting right speed in challenge*/
double challengeRight(bool hasLeftLine, bool fullTurn, int maze, int count, double forward, double turnSpeed, double vLeft, double vRight){
		double frontKP=0.2;
	if (redError(149)!=-1&&hasLeftLine&&!fullTurn){
return turnSpeed-redError(149);
}
	if (fullTurn){
	if (count<10){//waits a bit before starting to turn so it doesn't hit the wall.
return forward;
}
else{
	return turnSpeed+10;//starts to turn after a bit
}
}	
return forward-findError(maze)*frontKP;
}

/**function for setting left speed in core and completion*/
double corempletionLeft(int maze, bool sideLine, bool rightTurn, double vLeft, double forward, double turnSpeed, double vRight){
	double sideKP = 0.25;
	double frontKP = 0.1;
	  if (!sideLine&&findError(maze)!=-1){
      return forward+findError(maze)*frontKP;
  }
   else {
	   if (sideError(0)>0&&sideError(149)==-1){
		   return turnSpeed-sideError(0)*sideKP;
	   }
	   else if (sideError(149)>0&&rightTurn){
		  return turnSpeed+sideError(149)*sideKP;
	   }
  }
}

/**function for setting right speed in completion*/
double corempletionRight(int maze, bool sideLine, bool rightTurn, double vLeft, double forward, double turnSpeed, double vRight){
	double sideKP = 0.25;
	double frontKP = 0.1;
	  if (!sideLine&&findError(maze)!=-1){
	  return forward-findError(maze)*frontKP;
  }
   else {
	   if (sideError(0)>0&&sideError(149)==-1){
		   return turnSpeed+sideError(0)*sideKP;
	   }
	   else if (sideError(149)>0&&rightTurn){
		   return turnSpeed-sideError(149)*sideKP;
	   }
  }
}


int main(){
	int count=0;
	int maze;
	std::cout<<"Please enter 1 for core and completion, and 2 for challenge: ";
	std::cin>>maze;
	while (maze!=1&&maze!=2){
		std::cout<<"That's not right, please only enter 1 or 2: ";
		std::cin>>maze;
	}
	double forward = 40.0;
	double turnSpeed = 20.0;
	bool sideLine = false;//changes to true when line detected on sides closer to robot, changes back to false when no line is detected
	bool rightTurn = true;//sets to false when a left turn is picked up so it doesn't turn back to the previous line being followed when that ends
	//up on the right of the image, sets back to true once no line detected on left
	bool hasLeftLine=false;
	bool fullTurn = false;
	double sideKP = 0.25;
	double frontKP = 0.1;
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	} 
    double vLeft;
    double vRight;
    while(1){
      takePicture();
      if (maze==1){
		   /**if (sideLine&&sideError(0)>0&&sideError(149)==-1){rightTurn=false;}
		  if (sideError(0)==-1){rightTurn=true;}
if (sideError(0)>=70.0||sideError(149)>=70.0){sideLine=true;}
		if (sideError(0)==-1&&(sideError(149)==-1||!rightTurn)){sideLine=false;}
		vRight = corempletionRight(maze, sideLine, rightTurn, vLeft, forward, turnSpeed, vRight);
		vLeft = corempletionLeft(maze, sideLine, rightTurn, vLeft, forward, turnSpeed, vRight);*/
		if (sideError(0)>=70.0||sideError(149)>=70.0){sideLine=true;}
		if (sideError(0)==-1&&(sideError(149)==-1||!rightTurn)){sideLine=false;}
      if (!sideLine&&findError(maze)!=-1){
	  vRight=40.0-findError(maze)*frontKP;
      vLeft=40.0+findError(maze)*frontKP;
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
}
if (maze==2){
	if (findError(maze)==-1&&!hasRed(0)&&hasLeftLine){fullTurn=true;}
	if (findError(maze)!=-1){hasLeftLine=true;}
	if (fullTurn){count++;}
	if (count>0&&findError(maze)!=-1&&redError(149)==-1){
	fullTurn=false;
	count=0;
	}
	vRight = challengeRight(hasLeftLine, fullTurn, maze, count, forward, turnSpeed, vLeft, vRight);
	vLeft = challengeLeft(hasLeftLine, fullTurn, maze, count, forward, turnSpeed, vLeft, vRight);
}
      setMotors(vLeft,vRight);
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
