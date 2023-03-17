#ifndef GOLF_H
#define GOLF_H

#define MINIGOLF_HOLE_X 388.0
#define MINIGOLF_HOLE_Y 999.0
#define ARM_LENGTH 0.48

#include "uvision.h"
#include "upose.h"

struct Pos{
	float x;
	float y;
}; 

void run_golf_seesaw();
void run_mini_golf();
UPose* go_to_golfball(float ball_x,float ball_y);
void capture_ball();
bool InHole(Pos ball);
#endif