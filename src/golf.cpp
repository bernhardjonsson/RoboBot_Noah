
#include <iostream>
#include<cmath>
#include <string>

#include "PointToPoint.h"
#include "uevent.h"
#include "ubridge.h"
#include "uvision.h"
#include "upose.h"
#include "golf.h"

using namespace std;



void run_golf_seesaw(){

	vision.processImage(20);
	if(vision.ball_found == true){

		go_to_golfball(vision.ball_x[0],vision.ball_y[0]);
    	// capture the golf ball
		capture_ball();

		// go to hole

	}
}


void run_mini_golf(){
	Pos cur_ball;
	float angle;
	UPose* curr_pose;

	curr_pose->x = 0;
	curr_pose->y = 0;
	curr_pose->h = 0;

	for(int run=1; run<=4;run++)
	{
		printf("Performing run: %d of 4\n", run);
		vision.processImage(20);
		if(vision.ball_found == true){
			for(int i=0; i<vision.detected_balls; i++)
			{
				// extract current golf ball position
				cur_ball.x = vision.ball_x[i];
				cur_ball.y = vision.ball_y[i];

				// calculate if ball is not in hole
				printf("Working with ball in pos: (%.3f,%.3f)\n", cur_ball.x,cur_ball.y);
				if (InHole(cur_ball) == false){
					// go to golf ball
					curr_pose = &go_to_golfball(cur_ball->x,cur_ball->y);
					// pick it up
					capture_ball();

					// put in hole
					PointToPoint p2p;
					UPose endpose;

					angle = atan2(MINIGOLF_HOLE_Y - *curr_pose->y, MINIGOLF_HOLE_X - curr_pose->x);
					endpose.x =  MINIGOLF_HOLE_X - *curr_pose->x - ARM_LENGTH*cos(angle);
					endpose.y = MINIGOLF_HOLE_Y - *curr_pose->y - ARM_LENGTH*sin(angle);
					endpose.h = angle;
					printf("Robot at pose: (%.3f,%.3f,%.3f) in world frame\n", curr_pose->x,curr_pose->y,curr_pose->h);
					printf("Going to hole: (%.3f,%.3f) in world frame, (%.3f,%.3f) in robot frame\n", MINIGOLF_HOLE_X,MINIGOLF_HOLE_Y,endpose.x,endpose.y);
					p2p.goToPoint(&curr_pose, &endpose, 0.1, 0.5);
					curr_pose = endpose;

					// release ball
					printf("Releasing golf ball\n");
					bridge.tx("regbot mclear\n");
					event.clearEvents();
					bridge.tx("regbot madd servo=1,pservo=1000,vservo=130:time=1\n");
					bridge.tx("regbot start\n");
					event.waitForEvent(0);
					
					// go to origin
					angle = atan2(0 - curr_pose->y, 0 - curr_pose->x);
					endpose.x =  0 - curr_pose->x - ARM_LENGTH*cos(angle);
					endpose.y = 0 - curr_pose->y - ARM_LENGTH*sin(angle);
					endpose.h = angle;
					printf("Going to origin, (%.3f,%.3f) in robot frame\n",endpose.x,endpose.y);
					p2p.goToPoint(&startpose, &endpose, 0.1, 0.5);
					curr_pose = endpose;
					// when golf ball is in hole go to orgini and repeat
					break;
				}
				printf("Current golf ball in hole !\n");
			}
		}
	}
	
}

UPose* go_to_golfball(float ball_x,float ball_y){
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
	UPose endpose;
		
	endpose.x = ball_x - ARM_LENGTH*cos(angle);
	endpose.y = ball_y - ARM_LENGTH*sin(angle);
	endpose.h = angle;
	goToTest.goToPoint(&startpose, &endpose, 0.1, 0.5);
	return &endpose;
}

void capture_ball()
{
	// capture the golf ball
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=-50,vservo=125:time=1\n");
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

