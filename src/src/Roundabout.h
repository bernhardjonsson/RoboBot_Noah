#ifndef ROUNDABOUTMISSION_H
#define ROUNDABOUTMISSION_H

#include "ubridge.h"
#include "uevent.h"
#include "uirsensor.h"
#include "upose.h"
#include "PointToPoint.h"

#define MAX_ITER 1e3
#define EPSILON 0.1
using namespace std;
class RoundaboutMission
{
private:
    string velocity;
    string acceleration;
    string distance;
    string distanceMax;
    string irDistance;
public:
    RoundaboutMission(float vel, float acc,float distance, float irDistance, float distanceMax);
    ~RoundaboutMission();
    void runMission();
    void runMissionTest();
    void doRoundabout();
    void waitForRoundabout();
    void goToCarousel();
    void recoverRoundabout(string velocity, string distance);
};



#endif