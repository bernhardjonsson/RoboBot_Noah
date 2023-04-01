#ifndef GOLF_H
#define GOLF_H

#define MINIGOLF_HOLE_X 1.34
#define MINIGOLF_HOLE_Y 0.43
#define ARM_LENGTH 0.40

#include "uvision.h"
#include "upose.h"

struct Pos{
	float x;
	float y;
}; 


void run_golf_seesaw();
void run_mini_golf();
void go_to_golfball(float ball_x,float ball_y, UPose* curr_pose);
void move_arm(int servo, int pos, int vel, int time);
bool InHole(Pos ball);
void minigolf_run();
void capture_ball(); // should be unused

#endif
