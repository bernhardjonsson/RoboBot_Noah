#ifndef GOLF_H
#define GOLF_H

#define MINIGOLF_HOLE_X 1.2
#define MINIGOLF_HOLE_Y 0.33
#define ARM_LENGTH 0.48
#define PI 3.142

#include "uvision.h"
#include "upose.h"

struct Pos{
	float x;
	float y;
}; 


void run_golf_seesaw();
void run_mini_golf();
void go_to_golfball(float ball_x,float ball_y, UPose* curr_pose);
void capture_ball();
bool InHole(Pos ball);
void minigolf_test();

#endif