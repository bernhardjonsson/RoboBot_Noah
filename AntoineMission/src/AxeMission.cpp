#include "AxeMission.h"


AxeMission::AxeMission(float vel,float acc,float distance, float irDistance,float distanceMax)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
    this->distance = to_string(distance);
    this->irDistance = to_string(irDistance);
    this->distanceMax = to_string(distanceMax);
}

AxeMission::~AxeMission()
{
}

void AxeMission::runMission(){
    string cmd;
    int waitIter = 0;
    while(irsensor.ir2 <= stof(this->irDistance) + EPSILON){
        waitIter++;
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }
    if (waitIter != 0){
        this->goToRaceTrack();
    }
    else{
       while(irsensor.ir2 >= stof(this->irDistance) + EPSILON){
        waitIter++;
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
        }
        while(irsensor.ir2 <= stof(this->irDistance) + EPSILON){
        waitIter++;
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
        }
        this->goToRaceTrack();
    }
    

}

void AxeMission::goToAxe()
{
    string cmd;
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx(("regbot madd vel=0.3,acc="+this->acceleration+":dist=0.2\n").c_str());
    cmd = "regbot madd vel=0.3,acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edger=0,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    PointToPoint utils;
    UPose target_pose;
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    utils.goToPoint(&pose,&target_pose,stof(this->velocity),stof(this->acceleration),0.3);
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel=0.3,acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edger=0,white=1:dist=0.55,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}

void AxeMission::goToRaceTrack()
{
    string cmd;
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    bridge.tx("regbot madd vel=0 : time = 0.2\n");
    cmd = "regbot madd vel="+this->velocity + ",acc=" + this->acceleration +
                +":dist=" + this->distance + "\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.4,acc=" + this->acceleration +
                +":dist=1,lvl>12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0 : time = 0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    PointToPoint utils;
    UPose target_pose;
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    utils.goToPoint(&pose,&target_pose,stof(this->velocity),stof(this->acceleration),0.3);
}