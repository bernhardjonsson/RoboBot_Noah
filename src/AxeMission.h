#ifndef AXEMISSION_H
#define AXEMISSION_H

#include "ubridge.h"
#include "uevent.h"
#include "uirsensor.h"
#include "PointToPoint.h"

#define MAX_ITER 1e3
#define EPSILON 0.1
using namespace std;
class AxeMission
{
private:
    string velocity;
    string acceleration;
    string distance;
    string distanceMax;
    string irDistance;
public:
    AxeMission(float vel, float acc,float distance, float irDistance, float distanceMax);
    ~AxeMission();
    void runMission();
    void goToAxe();
    void goToRaceTrack();
};



#endif