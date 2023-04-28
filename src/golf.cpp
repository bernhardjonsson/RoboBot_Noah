
#include <iostream>
#include<cmath>
#include <string>
#include <fstream>
#include "PointToPoint.h"
#include "uevent.h"
#include "ubridge.h"
#include "uvision.h"
#include "upose.h"
#include "golf.h"
#include "FollowLine.h"

using namespace std;



void run_golf_seesaw(){
	float vel = 0.2;
  	float acc = 0.8; 
  	int level = 12; 
  	float distance = 10; 
  	bool rightOrLeft = 0;

  	// Start at the cross section
  	// Turn to seesaw
	// move_arm(1,1000,127,4);
	cout << "Turning to seesaw" << endl;
	PointToPoint goToBalance;
  	UPose targetPose;
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  90*PI/180; //Check angle
  /*  goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
  

  	// Go onto seesaw
	cout << "Going onto seesaw" << endl;
	bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.3,tr=0:turn=-30,lv>12\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

	FollowLine missionStartBalance(vel, acc, level, 0.1, rightOrLeft);
  	missionStartBalance.runMission();

  	targetPose.x = 0.25;
  	targetPose.y = 0;
  	targetPose.h = 0;
	vel = 0.2;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

  	// Go to and get golf ball
	FollowLine missionGoToBall(vel, acc, level, 0.795, rightOrLeft);
  	missionGoToBall.runMission();

	//capture_ball();

	move_arm(1,30,127,10);
	move_arm(1,60,127,5);



	// Go down seesaw
	cout << "Going down seesaw" << endl;
	rightOrLeft = 1;
  	vel = 0.1;
  	FollowLine missionEndBalance(vel, acc, level, 1.5, rightOrLeft);
  	missionEndBalance.runMission();

  	// Wait until balance is down
   	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd vel=0.0:time=2\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);
	

	vel = 0.3;
  	FollowLine missionEndBalance2(vel, acc, level, 1, rightOrLeft);
  	missionEndBalance2.runMission();


  	// Find the line up the incline
  	cout << "Going to next incline" << endl;
	// Manage metal (treated as a line)
	//targetPose.x = 5;
  	//targetPose.y = 0;
  	//targetPose.h = 0;
  	//goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);
	//targetPose.x = 0.1;
  	//targetPose.y = 0;
  	//targetPose.h = 0;
  	//goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);


  	targetPose.x = 5;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);

	
	PointToPoint goTo1;
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  -1*PI/2;
  	goTo1.goToPoint(&pose,&targetPose,vel,acc,0.2);
	
  	FollowLine mission3(vel, acc, level, 1.9, rightOrLeft);
  	mission3.runMission();
  	
	targetPose.x = 5;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);
	mission3.runMission();


	PointToPoint goTo2;
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  PI;
  	goTo2.goToPoint(&pose,&targetPose,vel,acc,0.2);
	
	move_arm(1,-40,125,5);
	
	cout << "Going up incline" << endl;
	vel = 0.15;
	FollowLine mission4(vel,acc,level,2,0);
	mission4.runMission();

	
	//Safety line lost
	targetPose.x = 0.1;
  	targetPose.y = 0;
  	targetPose.h =  0;
  	goTo2.goToPoint(&pose,&targetPose,vel,acc,0.2);
	FollowLine mission_safety_line(vel,acc,level,0.7,0);
	mission_safety_line.runMission();
*/
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd log=10: time=0.05\n");
	bridge.tx("regbot madd vel=0.3, acc=0.3, edgel=0.2, white=1: tilt<0.2, lv>12\n");
	bridge.tx("regbot madd edgel=0.2,white=1:tilt<0.2,lv<12\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);
  
	move_arm(1,0,125,1);	
	cout << "Putting ball in hole" << endl;
	PointToPoint goTo3;
  	targetPose.x = 0.40;
  	targetPose.y = 0.055;
  	targetPose.h = 0;
	vel = 0.15;
  	goTo3.goToPoint(&pose,&targetPose,vel,acc,0.2);

	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd log=10: time=0.05\n");
	bridge.tx("regbot madd label=10, vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=-45\n");
	bridge.tx("regbot madd vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=90\n");
	bridge.tx("regbot madd vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=-45\n");
	bridge.tx("regbot madd vel=0.1, acc=0.3: dist=0.01\n");
	bridge.tx("regbot madd goto=10: count=2\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);
	
	move_arm(1,1000,127,2);

	cout << "Finding line" << endl;
	// turn to line
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  -2.8;
	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
  	// going to line
  	targetPose.x = 1;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	vel = 0.5;
	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);

  	cout << "Going to crossing line" << endl;
  	// turning left
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  1.22;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);

  	// go to crossing
  	FollowLine mission98(vel, acc, level, 1.2, rightOrLeft);
  	mission98.runMission();
	rightOrLeft = 1;
  	FollowLine mission5(vel, acc, level, distance, rightOrLeft,1);
    	mission5.runMission();

  	// turning left
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = PI;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
	
	distance = 1.0;
	rightOrLeft = 0;
	FollowLine mission99(vel,acc,level,distance,rightOrLeft);
	mission99.runMission();

  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  PI/2;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
	

	cout << "Getting seccond ball" << endl;
	targetPose.x = 0.048;
  	targetPose.y = 0.025;
  	targetPose.h = 0;
	vel = 0.15;
  	goTo3.goToPoint(&pose,&targetPose,vel,acc,0.2);
	move_arm(1,-40,127,10);
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h =  -1*PI/2 - 0.5;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
	
	cout << "Going to hole" << endl;	
  	targetPose.x = 0.50;
  	targetPose.y = -0.327;
  	targetPose.h = 0;
	vel = 0.15;
  	goTo3.goToPoint(&pose,&targetPose,vel,acc,0.2);
	
	
	
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd log=10: time=0.05\n");
	bridge.tx("regbot madd label=10, vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=-40\n");
	bridge.tx("regbot madd vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=80\n");
	bridge.tx("regbot madd vel=0.0: time=0.05\n");
	bridge.tx("regbot madd vel=0.1, tr=0.0: turn=-40\n");
	bridge.tx("regbot madd vel=0.1, acc=0.3: dist=0.01\n");
	bridge.tx("regbot madd goto=10: count=2\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

	move_arm(1,1000,130,2);

	cout << "Going to start point" << endl;
    	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = PI/2 + 0.5;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);

  	// going to line
  	targetPose.x = 1;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	vel = 0.5;
	goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);
	
    	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = PI/2;
  	goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.2);
    	
	mission98.runMission();
	mission5.runMission();

}


void run_mini_golf(){
	Pos cur_ball;
	float angle;
	UPose* curr_pose = new UPose();

	curr_pose->x = 0;
	curr_pose->y = 0;
	curr_pose->h = 0;

	for(int run=1; run<=1;run++)
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
					//capture_ball();
					move_arm(1,50,125,5);

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
	startpose.x = curr_pose->x;
	startpose.y = curr_pose->y;
	startpose.h = curr_pose->h;
	
	PointToPoint goToTest;
	UPose* targetPose = new UPose();

	// position in robot frame
	targetPose->x = ball_x - ARM_LENGTH*cos(angle);
	targetPose->y = ball_y - ARM_LENGTH*sin(angle);
	targetPose->h = angle;

	// translate to world frame
	curr_pose->x = cos(startpose.h)*(targetPose->x) - sin(startpose.h)*(targetPose->y) + startpose.x;
	curr_pose->y = sin(startpose.h)*(targetPose->x) + cos(startpose.h)*(targetPose->y) + startpose.y;
	curr_pose->h = angle + startpose.h;//atan2(curr_pose->y,curr_pose->x);
	
	printf("want  to go to (ball):\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	
	
	goToTest.goToPointWorldCoordinates(&startpose,curr_pose, 0.1, 0.5);
}

void minigolf_run(){
	ofstream logfile;
	logfile.open("golflog.txt");
	printf("rungolf\n");
	float vel = 0.2;
  	float acc = 0.8; 
  	int level = 12; 
  	float distance = 10; 
  	bool rightOrLeft = 0;
  	UPose targetPose;
	Pos cur_ball;
	UPose* curr_pose = new UPose();

	curr_pose->x = 0;
	curr_pose->y = 0;
	curr_pose->h = 0;

	logfile << to_string(curr_pose->x) + "\t" + to_string(curr_pose->y) + "\t" +to_string(curr_pose->h) + "\n"; 
	
	vision.processImage(15);
	
	printf("balls arrays:\n");
	vision.printArray(vision.ball_x,6);
	vision.printArray(vision.ball_y,6);
	// extract current golf ball position
	
	cur_ball.x = vision.ball_x[0];
	cur_ball.y = vision.ball_y[0];
	printf("current ball coordinates\n");
	cout << "x : " + to_string(cur_ball.x) << endl;
    cout << "y : " + to_string(cur_ball.y) << endl;
	
	printf("going to ball\n");
	logfile << to_string(cur_ball.x) + "\t" + to_string(cur_ball.y) + "\t" +to_string(0) + "\n";


	go_to_golfball(cur_ball.x, cur_ball.y, curr_pose); // updates curr_pose
	sleep(1);	
	printf("robot now at:\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	logfile << to_string(curr_pose->x) + "\t" + to_string(curr_pose->y) + "\t" +to_string(curr_pose->h) + "\n";


	vision.processImage(15);
	cur_ball.x = vision.ball_x[0];
        cur_ball.y = vision.ball_y[0];
	go_to_golfball(cur_ball.x, cur_ball.y, curr_pose);
	logfile << to_string(cur_ball.x) + "\t" + to_string(cur_ball.y) + "\t" +to_string(0) + "\n";
	//capture_ball();	
	move_arm(1,45,125,10);
	printf("robot now at:\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	logfile << to_string(curr_pose->x) + "\t" + to_string(curr_pose->y) + "\t" +to_string(curr_pose->h) + "\n";
	
	PointToPoint p2p;

	float angle;
	UPose endpose;
	UPose localpose;
	localpose.x = 0;
	localpose.y = 0;
	localpose.h = 0;
	
	UPose goto_pose;
	
	// calculate hole pose
	angle = atan2(MINIGOLF_HOLE_Y - curr_pose->y, MINIGOLF_HOLE_X - curr_pose->x);
	goto_pose.x = MINIGOLF_HOLE_X - ARM_LENGTH*cos(angle);
	goto_pose.y = MINIGOLF_HOLE_Y - ARM_LENGTH*sin(angle);
	goto_pose.h = angle;
	
	printf("want  to go to (hole):\n");
	cout << "x : " + to_string(goto_pose.x) << endl;
    cout << "y : " + to_string(goto_pose.y) << endl;
    cout << "h : " + to_string(goto_pose.h) << endl;
	printf("\n");
	logfile << to_string(goto_pose.x) + "\t" + to_string(goto_pose.y) + "\t" +to_string(goto_pose.h) + "\n";
	p2p.goToPointWorldCoordinates(curr_pose, &goto_pose, 0.1, 0.5);

	// release ball
	printf("Releasing golf ball\n");
	move_arm(1,1000,130,1);
	
	curr_pose->x  = goto_pose.x;
	curr_pose->y  = goto_pose.y;
	curr_pose->h  = goto_pose.h;
	
	printf("vector to origin :\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    cout << "y : " + to_string(curr_pose->y) << endl;
    cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	
	goto_pose.x = 0.3;
	goto_pose.y = -0.5;
	goto_pose.h = 0;
	
	logfile << to_string(goto_pose.x) + "\t" + to_string(goto_pose.y) + "\t" +to_string(goto_pose.h) + "\n";
	
	printf("want  to go to (origin):\n");
	cout << "x : " + to_string(goto_pose.x) << endl;
    	cout << "y : " + to_string(goto_pose.y) << endl;
    	cout << "h : " + to_string(goto_pose.h) << endl;
	printf("\n");
	
	p2p.goToPointWorldCoordinates(curr_pose, &goto_pose, 0.1, 0.5);
	curr_pose->x  = goto_pose.x;
	curr_pose->y  = goto_pose.y;
	curr_pose->h  = goto_pose.h;
	printf("current pose :\n");
	cout << "x : " + to_string(curr_pose->x) << endl;
    	cout << "y : " + to_string(curr_pose->y) << endl;
    	cout << "h : " + to_string(curr_pose->h) << endl;
	printf("\n");
	

	PointToPoint goToOrigin;
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = -0.9;
	goToOrigin.goToPoint(&pose,&targetPose,vel,acc,0.2);
	logfile << to_string(targetPose.x) + "\t" + to_string(targetPose.y) + "\t" +to_string(targetPose.h) + "\n";
  	targetPose.x = 5;
  	targetPose.y = 0;
  	targetPose.h = 0;
  	goToOrigin.goToPointUntilLineReached(&targetPose,0.4,acc,0.2);
	
	
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = -PI/2;
	goToOrigin.goToPoint(&pose,&targetPose,vel,acc,0.2);
	logfile << to_string(targetPose.x) + "\t" + to_string(targetPose.y) + "\t" +to_string(targetPose.h) + "\n";

	cout << "Following line " << endl;
  	FollowLine Origin(vel, acc, level, distance, rightOrLeft);
    Origin.runMission();
  	targetPose.x = 0;
  	targetPose.y = 0;
  	targetPose.h = -1.8;
	goToOrigin.goToPoint(&pose,&targetPose,vel,acc,0.2);
	logfile << to_string(targetPose.x) + "\t" + to_string(targetPose.y) + "\t" +to_string(targetPose.h) + "\n";
	logfile.close();
}


void capture_ball()
{
	// capture the golf ball
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=50,vservo=125:time=10\n");
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

void move_arm(int servo, int pos, int vel, int time)
{
	string cmd;
	bridge.tx("regbot mclear\n");
	event.clearEvents();
	cmd = "regbot madd servo="+to_string(servo)+",pservo="+to_string(pos)+
				",vservo="+to_string(vel)+":time="+to_string(time)+"\n";
	bridge.tx(cmd.c_str());
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

}
