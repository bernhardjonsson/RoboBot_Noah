#include "PointToPoint.h"

PointToPoint::PointToPoint(){

}

PointToPoint::~PointToPoint(){}

void PointToPoint::goToPoint(UPose* currentPose,UPose* targetPose, float speed, float acc){
    cout << "x : " + to_string(currentPose->x) << endl;
    cout << "y : " + to_string(currentPose->y) << endl;
    cout << "h : " + to_string(currentPose->h) << endl;
    float dist = computeDistance(currentPose, targetPose);

    float alpha = atan2(targetPose->y-currentPose->y,targetPose->x-currentPose->x);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");

    string cmdHead = "regbot madd vel=" + to_string(speed) + ",tr=0:turn=" + to_string(radToDeg(alpha) - radToDeg(currentPose->h)) + "\n";
    string cmdDist = "regbot madd vel=" + to_string(speed) + ",acc=" + to_string(acc) + 
                    ":dist=" + to_string(dist) + "\n";
    cout << "Angle : " + to_string(radToDeg(alpha) - radToDeg(currentPose->h)) << endl;
    cout << "Distance : "+ to_string(dist) << endl;
    bridge.tx(cmdHead.c_str());
    bridge.tx("regbot madd vel=0.0: time=0.1\n");
    bridge.tx(cmdDist.c_str());
    bridge.tx("regbot madd vel=0:time=0.05\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    cmdHead = "regbot madd vel=" + to_string(speed) + "tr=0:turn=" + to_string(radToDeg(targetPose->h) - radToDeg(alpha)) + "\n";

    bridge.tx(cmdHead.c_str());
    bridge.tx("regbot madd vel=0:time=0.05\n");
    bridge.tx("regbot start\n");
    cout << "Mission should start!" << endl;
    event.waitForEvent(0);

}

void PointToPoint::goToPointWorldCoordinates(UPose* currentPose,UPose* targetPose, float speed, float acc){
    UPose targetPoseRobotFrame;
    targetPoseRobotFrame.x = cos(targetPose->h)*targetPose->x + sin(targetPose->h)*targetPose->y - currentPose->x;
    targetPoseRobotFrame.y = -sin(targetPose->h)*targetPose->x + cos(targetPose->h)*targetPose->y - currentPose->y;
    targetPoseRobotFrame.h = targetPose->h - currentPose->h;
    goToPoint(currentPose,&targetPoseRobotFrame,speed,acc);
}

float PointToPoint::computeDistance(UPose* currentPose,UPose* targetPose){
    float dist = sqrt(pow(targetPose->x - currentPose->x,2) + pow(targetPose->y - currentPose->y,2));
    return dist;
}

float PointToPoint::computeOrientation(UPose* currentPose,UPose* targetPose){
    float orientation = wrapToPi(targetPose->h - currentPose->h);
    return orientation;
}

float PointToPoint::radToDeg(float rad){
    return rad*180/PI;
}

float PointToPoint::wrapToPi(float angle){
    if ((angle < -PI) || (PI <   angle)){
        return wrapTo2Pi(angle + PI) - PI;
    }
   else {
    return angle;
   }
}

float PointToPoint::wrapTo2Pi(float angle){
    bool positiveInput = angle > 0;
    float wrappedAngle = angle - floor(angle /((float) 2*PI))*((float)2*PI);
    if (angle == 0 && positiveInput){
        return 2*PI;
    }
    else{
        return wrappedAngle;
    }
}