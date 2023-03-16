#ifndef POINT_TO_POINT_H
#define POINT_TO_POINT_H


#include "ubridge.h"
#include "uevent.h"
#include "upose.h"
#include <cmath>

//class UPose;
#define PI 3.14159265359
using namespace std;
class PointToPoint
{
private:
    float computeDistance(UPose* currentPose, UPose* targetPose);
    float computeOrientation(UPose* currentPose, UPose* targetPose);
    float radToDeg(float rad);
    float wrapToPi(float angle);
    float wrapTo2Pi(float angle);
public:
    PointToPoint();
    ~PointToPoint();
    void goToPoint(UPose* currentPose,UPose* targetPose, float speed, float acc);
    void goToPointWorldCoordinates(UPose* currentPose,UPose* targetPose, float speed, float acc);
};

extern PointToPoint pointtest;

#endif
