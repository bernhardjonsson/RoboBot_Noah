#include "FollowLine.h"



FollowLine::FollowLine(float vel,float acc,int level,
        float distance, bool rightOrLeft)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
    this->level = to_string(level);
    this->distance = to_string(distance);
    this->rightOrLeft = rightOrLeft;

}

FollowLine::FollowLine(float vel,float acc,int level,
        float distance, bool rightOrLeft,bool stopOnCrossLine)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
    this->level = to_string(level);
    this->distance = to_string(distance);
    this->rightOrLeft = rightOrLeft;
    this->stopOnCrossLine = stopOnCrossLine;

}

FollowLine::~FollowLine()
{
}

void FollowLine::runMission()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    string cmd;
    string stopCondition;
    if(rightOrLeft){
        cmd = "vel="+this->velocity+
                    ",acc="+this->acceleration+
                    ",edger=0,white=1:dist=0.1"+
                    ",lv>"+this->level;
        stopCondition = "edger=0,white=1:dist="+this->distance+
                                ",lv<"+this->level;         
    }
    else{
        cmd = "vel="+velocity+
                    ",acc="+this->acceleration+
                    ",edgel=0.2,white=1:dist="+this->distance+
                    ",lv>"+this->level;
        stopCondition = "edgel=0.2,white=1:dist="+this->distance+
                                ",lv<"+this->level;
    }
    if(this->stopOnCrossLine)
    {
        stopCondition += ",xl>10";
    }
    string cmdBridge = "regbot madd " + cmd + "\n";
    string stopConditionBridge = "regbot madd " + stopCondition + "\n";
    bridge.tx(cmdBridge.c_str());
    bridge.tx(stopConditionBridge.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}

