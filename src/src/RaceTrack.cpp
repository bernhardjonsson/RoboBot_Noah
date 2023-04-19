#include "RaceTrack.h"

RaceTrackMission::RaceTrackMission(float vel, float acc)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
}

void RaceTrackMission::runMission()
{
    string cmd;
    // Stop before turn
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.3,acc=0.8,edger=0.3,white=1:dist=0.1,lv<12\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx(("regbot madd vel="+this->velocity+",acc="+this->acceleration+":dist=0.2\n").c_str());
    cmd = "regbot madd vel=" + this->velocity +",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=" + this->velocity + "edger=0.3,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0.5,tr=0.0:turn=-87\n");
    bridge.tx(("regbot madd vel="+ this->velocity +",acc="+this->acceleration+":dist=0.1\n").c_str());
    bridge.tx(("regbot madd vel="+this->velocity+",acc="+this->acceleration+":dist=5,lv > 12\n").c_str());
    bridge.tx("regbot madd vel=0:time=0.1\n");
    /*cmd = "regbot madd vel=0.5,edger=0,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());*/
    /*bridge.tx("regbot madd vel=0.5,tr=0:turn=-30\n");
    bridge.tx(("regbot madd vel=0.3,acc="+this->acceleration+":dist=3,lv > 12\n").c_str());
    cmd = "regbot madd vel=0.3,edger=0,white=1:dist=1.75,lv<12\n";
    bridge.tx(cmd.c_str());*/
    /*cmd = "regbot madd vel=0.5,edger=0,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=" + this->velocity + "edger=0,white=1:dist=6,lv<12\n";
    bridge.tx(cmd.c_str());*/
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.5,tr=0:turn=-90\n");
    bridge.tx("regbot madd vel=0:time=0.1\n");
    bridge.tx(("regbot madd vel=0.3,acc="+this->acceleration+":dist=3,lv > 12\n").c_str());
    cmd = "regbot madd vel=" + to_string(0.7) + "edger=0.3,white=1:dist=6,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    /*
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx(("regbot madd vel="+this->velocity+",acc="+this->acceleration+":dist=0.5\n").c_str());
    cmd = "regbot madd vel="+this->velocity+
              ",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
        bridge.tx(cmd.c_str());
    cmd = "regbot madd vel="+this->velocity+",edger=0,white=1:dist=12,lv<12\n";
    bridge.tx(cmd.c_str());
    //bridge.tx(("regbot madd vel="+to_string(velocity)+": dist = 0.05\n").c_str());
    //bridge.tx(("regbot madd vel"+velocity+",acc="+this->acceleration+":dist=0.1\n").c_str());
    //bridge.tx("regbot madd vel=0 : time = 0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);*/
    /*PointToPoint race;
    UPose target_pose;
    target_pose.x = 1.80;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    race.goToPoint(&pose, &target_pose, stod(this->velocity),stod(this->acceleration),0.5);
    target_pose.x = 8;
    target_pose.y = 0;
    target_pose.h = 0;
    race.goToPointUntilLineReached(&target_pose, stod(this->velocity),stod(this->acceleration),0.5);*/

}