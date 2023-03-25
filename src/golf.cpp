
#include <iostream>
#include<cmath>
#include <string>

#include "PointToPoint.h"
#include "uevent.h"
#include "ubridge.h"
#include "uvision.h"
#include "upose.h"
#include "golf.h"
#include "FollowLine.h"

using namespace std;



void run_golf_seesaw(){
	float vel = 0.5;
  	float acc = 0.8; 
  	int level = 12; 
  	float distance = 10; 
  	bool rightOrLeft = 0;

	PointToPoint goToBalance;
  	UPose targetPose;
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  1.2217;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);
  	FollowLine missionStartBalance(vel, acc, level, 0.1, rightOrLeft);
  	missionStartBalance.runMission();

  	targetPose.x = 0.3;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);
  
  	// Golf ball mission
	vision.processImage(20);
	if(vision.ball_found == true){

		go_to_golfball(vision.ball_x[0],vision.ball_y[0], curr_pose);
    	// capture the golf ball
		capture_ball();
	}

	rightOrLeft = 1;
  	vel = 0.3;
  	FollowLine missionEndBalance(vel, acc, level, 1.5, rightOrLeft);
  	missionEndBalance.runMission();

  	// Wait until balance is down
   	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd vel=0.0:time=5\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

  	FollowLine missionEndBalance2(vel, acc, level, 1, rightOrLeft);
  	missionEndBalance2.runMission();

  	targetPose.x = 1;
  	targetPose.y = 0;
  	targetPose.h = -PI/2;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

  	targetPose.x = 5;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);

  	targetPose.x = 0.2;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

  	targetPose.x = 5;
  	targetPose.y = 0;
  	targetPose.h = -1.2217;
  	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);
}


void run_mini_golf(){
	Pos cur_ball;
	float angle;
	UPose* curr_pose = new UPose();

	curr_pose->x = 0;
	curr_pose->y = 0;
	curr_pose->h = 0;

	for(int run=1; run<=4;run++)
	{
		printf("Performing run: %d of 4\n", run);
		vision.processImage(20);
		if(vision.ball_found == true){
			for(int i=0; i<6; i++)
			{
				vision.printArray(vision.ball_x,6);
				vision.printArray(vision.ball_y,6);
				// extract current golf ball position
				cur_ball.x = vision.ball_x[i];
				cur_ball.y = vision.ball_y[i];
				if(cur_ball.x != 0 && cur_ball.y != 0){
				// calculate if ball is not in hole
				printf("Working with ball in pos: (%.3f,%.3f)\n", cur_ball.x,cur_ball.y);
				if (InHole(cur_ball) == false){
					// go to golf ball
					go_to_golfball(cur_ball.x,cur_ball.y, curr_pose);
					// pick it up
					capture_ball();

					// put in hole
					PointToPoint p2p;
					UPose endpose;

					angle = atan2(MINIGOLF_HOLE_Y - curr_pose->y, MINIGOLF_HOLE_X - curr_pose->x);
					endpose.x =  MINIGOLF_HOLE_X - ARM_LENGTH*cos(angle); //- curr_pose->x
					endpose.y = MINIGOLF_HOLE_Y - ARM_LENGTH*sin(angle);//- curr_pose->y
					endpose.h = angle;
					printf("Robot at pose: (%.3f,%.3f,%.3f) in world frame\n", curr_pose->x,curr_pose->y,curr_pose->h);
					printf("Going to hole: (%.3f,%.3f) in world frame, (%.3f,%.3f) in robot frame\n", MINIGOLF_HOLE_X,MINIGOLF_HOLE_Y,endpose.x,endpose.y);
					p2p.goToPointWorldCoordinates(curr_pose, &endpose, 0.1, 0.5);
					curr_pose = &endpose;

					// release ball
					printf("Releasing golf ball\n");
					bridge.tx("regbot mclear\n");
					event.clearEvents();
					bridge.tx("regbot madd servo=1,pservo=1000,vservo=130:time=10\n");
					bridge.tx("regbot start\n");
					event.waitForEvent(0);
					
					// go to origin
					angle = atan2(0 - curr_pose->y, 0 - curr_pose->x);
					endpose.x =  0;// - curr_pose->x - ARM_LENGTH*cos(angle);
					endpose.y = 0; //- curr_pose->y - ARM_LENGTH*sin(angle);
					endpose.h = 0;//angle;
					printf("Going to origin, (%.3f,%.3f) in robot frame\n",endpose.x,endpose.y);
					p2p.goToPointWorldCoordinates(curr_pose, &endpose, 0.1, 0.5);
					curr_pose = &endpose;
					// when golf ball is in hole go to orgini and repeat
					break;
				}
				
				printf("Current golf ball in hole !\n");
				}
			}
		}
	}
	
}

void go_to_golfball(float ball_x,float ball_y, UPose* curr_pose){
	float angle;
	float angled;
	float dist;
	// Calculate the input to teensy
	angle = atan2(ball_y, ball_x);
	angled = angle*180.0/3.1415;
	dist = sqrt(pow(ball_x,2) + pow(ball_y,2));
	printf("distance to ball: %.3f meters, angle: %.3f degrees\n", dist, angled);
		
	UPose startpose;
	startpose.x = 0;
	startpose.y = 0;
	startpose.h = 0;
	
	PointToPoint goToTest;

	curr_pose->x = ball_x - ARM_LENGTH*cos(angle);
	curr_pose->y = ball_y - ARM_LENGTH*sin(angle);
	curr_pose->h = angle;
	
	printf("want  to go to (ball):\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	
	
	goToTest.goToPoint(&startpose,curr_pose, 0.1, 0.5);
	
}

void minigolf_test(){
	Pos cur_ball;
	UPose* curr_pose = new UPose();

	curr_pose->x = 0;
	curr_pose->y = 0;
	curr_pose->h = 0;
	
	printf("Performing run 1");
	vision.processImage(20);
	
	printf("balls arrays:\n");
	vision.printArray(vision.ball_x,6);
	vision.printArray(vision.ball_y,6);
	// extract current golf ball position
	
	cur_ball.x = 1.5;//vision.ball_x[0];
	cur_ball.y = -0.5;//vision.ball_y[0];
	
	printf("current ball coordinates\n");
	cout << "x : " + to_string(cur_ball.x) << endl;
    cout << "y : " + to_string(cur_ball.y) << endl;
	
	printf("going to ball\n");

	go_to_golfball(cur_ball.x, cur_ball.y, curr_pose); // updates curr_pose
	
	printf("robot now at:\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	
	PointToPoint p2p;
	float angle;
	UPose endpose;
	UPose localpose;
	localpose.x = 0;
	localpose.y = 0;
	localpose.h = 0;
	
	UPose goto_pose;
	
	// calculate hole pose
	angle = atan2(MINIGOLF_HOLE_Y - curr_pose->y, MINIGOLF_HOLE_X - curr_pose->x) - PI/2 + curr_pose->h;
	goto_pose.x = MINIGOLF_HOLE_X - ARM_LENGTH*cos(angle);
	goto_pose.y = MINIGOLF_HOLE_Y - ARM_LENGTH*sin(angle);
	goto_pose.h = angle;
	
	printf("want  to go to (hole):\n");
	cout << "x : " + to_string(goto_pose.x) << endl;
    cout << "y : " + to_string(goto_pose.y) << endl;
    cout << "h : " + to_string(goto_pose.h) << endl;
	printf("\n");
	
	p2p.goToPointWorldCoordinates(curr_pose, &goto_pose, 0.1, 0.5);
	curr_pose->x  = goto_pose.x;
	curr_pose->y  = goto_pose.y;
	curr_pose->h  = goto_pose.h;
	
	printf("vector to origin :\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	
	goto_pose.x = 0;
	goto_pose.y = 0;
	goto_pose.h = 0;
	
	
	
	printf("want  to go to (origin):\n");
	cout << "x : " + to_string(goto_pose.x) << endl;
    cout << "y : " + to_string(goto_pose.y) << endl;
    cout << "h : " + to_string(goto_pose.h) << endl;
	printf("\n");
	
	p2p.goToPointWorldCoordinates(curr_pose, &goto_pose, 0.1, 0.5);
	curr_pose->x  = goto_pose.x;
	curr_pose->y  = goto_pose.y;
	curr_pose->h  = goto_pose.h;
	
	
	
	
	

}


void capture_ball()
{
	// capture the golf ball
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=-50,vservo=125:time=10\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);
}

bool InHole(Pos ball){
	float dist;
	dist = sqrt(pow(ball.x - MINIGOLF_HOLE_X,2) + pow(ball.y - MINIGOLF_HOLE_Y,2));
	if (dist < 0.12){
		return true;
	}
	return false;
}

