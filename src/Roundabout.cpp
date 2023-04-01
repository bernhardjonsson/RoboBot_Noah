#include "Roundabout.h"


RoundaboutMission::RoundaboutMission(float vel,float acc,float distance, float irDistance,float distanceMax)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
    this->distance = to_string(distance);
    this->irDistance = to_string(irDistance);
    this->distanceMax = to_string(distanceMax);
}

RoundaboutMission::~RoundaboutMission()
{
}

void RoundaboutMission::runMission(){
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    string cmd;
    cmd = "regbot madd vel="+this->velocity + ",acc=" + this->acceleration +
        ":ir2<" + this->irDistance + + ",dist=" + this->distance + "\n";
    //cmd = "regbot madd vel="+this->velocity + ":dist=" + this->distanceMax + "\n";
    bridge.tx(cmd.c_str());
    /*bridge.tx("regbot madd vel=0.3:dist=0.3\n");
    bridge.tx("regbot madd vel=0 : time = 0.1\n");*/
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
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
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        cmd = "regbot madd vel="+this->velocity+
              ",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>16\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel="+this->velocity+
              "tr=0:turn="+to_string(90)+"\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel="+this->velocity + ",edger=0 white=1:dist=8,lv<16,ir2<0.3" + "\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
        if(irsensor.ir2 <= 0.35){
            float dist_done = pose.t*std::stof(this->velocity);
            float new_dist = stod(distanceMax) - dist_done;
            float new_velocity = std::stof(this->velocity) - 0.1;
            bridge.tx("regbot mclear\n");
            event.clearEvents();
            bridge.tx("regbot madd log=10:time=0.05\n");
            cmd = "regbot madd vel="+to_string(new_velocity)+
                  ",acc="+this->acceleration+
                  ",edger=0,white=1:dist=0.05"+
                  ",lv>16\n";
            bridge.tx(cmd.c_str());
            cmd = "regbot madd vel="+this->velocity + ",edger=0 white=1:dist="+to_string(new_dist) + ",lv<16"+ "\n";
            bridge.tx(cmd.c_str());
            bridge.tx("regbot madd vel=0 : time = 0.1\n");
            bridge.tx("regbot start\n");
            event.waitForEvent(0);

        }

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
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        cmd = "regbot madd vel="+this->velocity+
              ",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>16\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel="+this->velocity+
              "tr=0:turn="+to_string(90)+"\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel="+this->velocity + ",edger=0 white=1:dist=8,lv<16,ir2<0.3" + "\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }
}

void RoundaboutMission::runMissionTest()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    string cmd;
    cmd = "regbot madd vel="+this->velocity + ",acc=" + this->acceleration +
        ":ir2<" + this->irDistance + + ",dist=" + this->distance + "\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    int waitIter = 0;
    bool irFlag = 0;
    while(irsensor.ir2 < stof(this->irDistance)){
        // Wait until there is some place to go in 
        waitIter++;
        this->waitForRoundabout();
    }
    if(waitIter > 0){
        this->doRoundabout();
        this->recoverRoundabout(this->velocity,to_string(2.5));
        irFlag = (irsensor.ir2 < 0.2 + EPSILON);
    }
    else{
        while(irsensor.ir2 > stof(this->irDistance))
        {
            this->waitForRoundabout();
        }
         while(irsensor.ir2 < stof(this->irDistance))
        {
            this->waitForRoundabout();
        }
        this->doRoundabout();
        this->recoverRoundabout(this->velocity,to_string(2.5));
        irFlag = (irsensor.ir2 < 0.2 + EPSILON);
    }
    if (irFlag)
    {
        float dist_done = pose.t*std::stof(this->velocity);
        float new_dist = stod(this->distanceMax) - dist_done;
        float new_velocity = std::stof(this->velocity) - 0.1;
        this->recoverRoundabout(to_string(new_velocity), to_string(new_dist));
        this->recoverRoundabout(this->velocity,to_string(4));
    }
    this->goToCarousel();
}
    

void RoundaboutMission::doRoundabout()
{
    string cmd;
    bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        cmd = "regbot madd vel=0.4,acc="+this->acceleration+
              ",edger=0,white=1:dist=5"+
              ",lv>12\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot madd vel=0:time=0.1\n");
        bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear \n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        cmd = "regbot madd vel="+this->velocity+
              "tr=0:turn="+to_string(90)+"\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
        event.clearEvents();
        cmd = "regbot madd vel="+this->velocity+
              ",acc="+this->acceleration+
              ":dist=0.1,lv>12\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel=0.3,edger=0,white=1:dist="+this->distanceMax+",lv<12,ir2<0.2,ir1<0.2\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot start\n");
    event.waitForEvent(0);

}

void RoundaboutMission::recoverRoundabout(string velocity, string distance)
{
    string cmd;
    bridge.tx("regbot mclear \n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        cmd = "regbot madd vel="+this->velocity+
              ",acc="+this->acceleration+
              ":dist=0.1\n";
        bridge.tx(cmd.c_str());
        cmd = "regbot madd vel=0.3,edger=0,white=1:dist="+distance+",lv<12,ir2<0.2\n";
        bridge.tx(cmd.c_str());
        bridge.tx("regbot start\n");
        event.waitForEvent(0);

}

void RoundaboutMission::waitForRoundabout()
{
    bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
}

void RoundaboutMission::goToCarousel()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.3,tr=0:turn=-90\n");
    bridge.tx("regbot madd vel=0.0:time=0.1\n");
    bridge.tx("regbot madd vel=0.3,acc=0.5:dist=0.6\n");
    bridge.tx("regbot madd vel=0.0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}