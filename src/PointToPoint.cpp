#include "PointToPoint.h"

PointToPoint::PointToPoint(){

}

PointToPoint::~PointToPoint(){}

void PointToPoint::goToPoint(UPose* currentPose,UPose* targetPose, float speed, float acc,float turningSpeed){
    cout << "x : " + to_string(currentPose->x) << endl;
    cout << "y : " + to_string(currentPose->y) << endl;
    cout << "h : " + to_string(currentPose->h) << endl;

    //float dist = computeDistance(currentPose, targetPose);
    dist = sqrt(targetPose->x * targetPose->x + targetPose->y*targetPose->y);

    float alpha = atan2(targetPose->y,targetPose->x);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");

    string cmdHead = "regbot madd vel=" + to_string(turningSpeed) + ",tr=0:turn=" + to_string(radToDeg(alpha)) + "\n";
    string cmdDist = "regbot madd vel=" + to_string(speed) + ",acc=" + to_string(acc) + 
                    ":dist=" + to_string(dist) + "\n";
    cout << "Angle : " + to_string(radToDeg(alpha)) << endl;
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
    cmdHead = "regbot madd vel=" + to_string(turningSpeed) + ",tr=0:turn=" + to_string(radToDeg(wrapToPi(targetPose->h)) - radToDeg(alpha)) + "\n";

    bridge.tx(cmdHead.c_str());
    bridge.tx("regbot madd vel=0:time=0.05\n");
    bridge.tx("regbot start\n");
    cout << "Mission should start!" << endl;
    event.waitForEvent(0);
}

void PointToPoint::goToPointUntilLineReached(UPose* targetPose, float speed, float acc, float turningSpeed){
    float dist = sqrt(targetPose->x * targetPose->x + targetPose->y*targetPose->y);
    float alpha = atan2(targetPose->y,targetPose->x);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");

    string cmdHead = "regbot madd vel=" + to_string(turningSpeed) + ",tr=0:turn=" + to_string(radToDeg(alpha)) + "\n";
    string cmdDist = "regbot madd vel=" + to_string(speed) + ",acc=" + to_string(acc) + 
                    ":dist=" + to_string(dist) + ",lv>16\n";
    cout << "Angle : " + to_string(radToDeg(alpha)) << endl;
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
    cmdHead = "regbot madd vel=" + to_string(turningSpeed) + ",tr=0:turn=" + to_string(radToDeg(wrapToPi(targetPose->h)) - radToDeg(alpha)) + "\n";

    bridge.tx(cmdHead.c_str());
    bridge.tx("regbot madd vel=0:time=0.05\n");
    bridge.tx("regbot start\n");
    cout << "Mission should start!" << endl;
    event.waitForEvent(0);
}
void PointToPoint::goToPointWorldCoordinates(UPose* currentPose,UPose* targetPose, float speed, float acc){
    UPose targetPoseRobotFrame;
    targetPoseRobotFrame.x = cos(currentPose->h)*(targetPose->x - currentPose->x) + sin(currentPose->h)*(targetPose->y - currentPose->x);
    targetPoseRobotFrame.y = -sin(currentPose->h)*(targetPose->x - currentPose->y) + cos(currentPose->h)*(targetPose->y - currentPose->y);
    targetPoseRobotFrame.h = targetPose->h + currentPose->h;
    currentPose->x = 0;
    currentPose->y = 0;
    currentPose->h = 0;
    cout << "x : " + to_string(targetPoseRobotFrame->x) << endl;
    cout << "y : " + to_string(targetPoseRobotFrame->y) << endl;
    cout << "h : " + to_string(targetPoseRobotFrame->h) << endl;
    goToPoint(currentPose,&targetPoseRobotFrame,speed,acc,0.3);
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