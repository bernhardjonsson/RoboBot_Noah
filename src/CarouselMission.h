#ifndef CAROUSEMISSION_H
#define CAROUSEMISSION_H

#include "ubridge.h"
#include "uevent.h"
#include "uirsensor.h"
#include "upose.h"
#include "PointToPoint.h"
#include "FollowLine.h"

#define MAX_ITER 1e3
#define EPSILON 0.1
using namespace std;
class CarouselMission
{
private:
    string velocity;
    string acceleration;
    string radius;
public:
    CarouselMission(float vel, float acc);
    CarouselMission(float vel, float acc, float radius);
    ~CarouselMission();
    void runMission();
    void doSquare();
    void doCircle();
    void do3rd_Circle(bool last_turn);
    void goNextGate(float radius);
    void goLastGate(float radius);
    void goToMiniGolf(string velocity);
    void waitUntilRobot();
};



#endif