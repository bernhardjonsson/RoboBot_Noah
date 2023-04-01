#include "CarouselMission.h"

CarouselMission::CarouselMission(float vel,float acc)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
}

CarouselMission::CarouselMission(float vel,float acc,float radius)
{
    this->velocity = to_string(vel);
    this->acceleration = to_string(acc);
    this->radius = to_string(radius);
}

CarouselMission::~CarouselMission()
{

}
void CarouselMission::doSquare()
{
    PointToPoint square_path;
    UPose targetPose;
    // Adjusting angle 
    targetPose.x = 0;
    targetPose.y = 0;
    targetPose.h = PI/3; //60 degrees
    square_path.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3);
    targetPose.x = 0.4;
    targetPose.y = 0;
    targetPose.h = -PI/2; //90 degrees
    for (int i=0; i<4;i++){
        square_path.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3);
    }
}

void CarouselMission::doCircle()
{
    PointToPoint square_path;
    UPose targetPose;
    // Adjusting angle 
    targetPose.x = 0;
    targetPose.y = 0;
    targetPose.h = PI/2; //90 degrees
    square_path.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3); // 90 degree turn
    
    this->goNextGate(0);
    this->goNextGate(0);
    this->goLastGate(0.335);
}

    void CarouselMission::goNextGate(float radius){
        // Go forward until encountering gate
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel="+this->velocity+",tr="+this->radius+":turn=-360, ir1 < 0.25\n").c_str()); // turn 120
        bridge.tx("regbot madd vel=0: time = 0.1\n"); // stop the robot
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
        // Adjust
        float distance = irsensor.ir1; 
        printf("\r\n IR DIST : %f \r\n",irsensor.ir1);

        float turn = 0.0;
        if (distance < 0.25){
            float K = 130;
            turn = (distance - 0.15)*K;
            printf("\r\n Error:%f Turn : %f \r\n",(distance - 0.15),turn);
        }


            // if (distance < 0.1){
        //     turn = -25;
        // }
        // else if(distance < 0.25){
        //     turn = -15;
        // }
        // else 
        // {
        //     turn = 0;
        // }

        // PointToPoint square_path;
        // UPose targetPose;
        // // Adjusting angle 
        // targetPose.x = 0;
        // targetPose.y = 0;
        // targetPose.h = turn*PI/180;
        // square_path.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3); // 90 degree turn
        
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel="+this->velocity+",tr= 0: turn="+to_string(-10)+"\n").c_str()); // adjust 5 deg
        bridge.tx("regbot madd vel=0: time = 0.1\n"); // stop the robot
        bridge.tx("regbot madd vel=0.1 : dist = 0.15\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }

      void CarouselMission::goLastGate(float radius){
        // Go forward without checking ir1
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel=0.3,tr="+to_string(radius)+":turn=-90\n").c_str()); // turn 60
        // bridge.tx("regbot madd vel=0: time = 0.1\n"); // stop the robot
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
        // Go forward until encountering gate
        printf("\r\n LAST PART\r\n");
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel="+this->velocity+",tr="+to_string(radius)+":turn=-120, ir1 < 0.25\n").c_str()); // turn 60
        bridge.tx("regbot madd vel=0: time = 0.1\n"); // stop the robot
        bridge.tx("regbot start\n");
        event.waitForEvent(0);

        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel="+this->velocity+",tr= 0: turn="+to_string(-20)+"\n").c_str()); // adjust 5 deg
        bridge.tx("regbot madd vel=0.25 : dist = 0.25\n");
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }

    void CarouselMission::do3rd_Circle(bool last_turn)
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    bridge.tx("regbot madd vel=0 : time = 0.3\n");
    bridge.tx(("regbot madd vel="+this->velocity+",tr="+this->radius+":turn=-120, ir1 < 0.25\n").c_str()); // turn 120
    bridge.tx("regbot madd vel=0: time = 0.1\n"); // stop the robot

    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    if(!last_turn){
        float distance = irsensor.ir1;
        float turn = 0.0;
        if (distance < 0.05){
            turn = -20;
        }
        else if(distance < 0.1){
            turn = -8;
        }
        else if(distance > 0.1){
            turn = 8;
        }
        else if(distance > 0.15){
            turn = 15;
        }
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd log=10:time=0.05\n");
        bridge.tx("regbot madd vel=0 : time = 0.3\n");
        bridge.tx(("regbot madd vel="+this->velocity+",tr= 0: turn="+to_string(turn)+"\n").c_str()); // adjust 5 deg
        bridge.tx("regbot madd vel=0.1 : dist = 0.1\n");
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }
    

    
}



void CarouselMission::runMission()
{
    //this->doSquare();
    this->doCircle();
    this->goToMiniGolf(to_string(0.5));
}

void CarouselMission::goToMiniGolf(string velocity)
{
    string cmd;
    this->waitUntilRobot();
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    bridge.tx("regbot madd vel=0 : time = 0.1\n");
    cmd = "regbot madd vel=" + velocity + ",acc="+this->acceleration+
              ",edger=0,white=1:dist=5"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    bridge.tx(("regbot madd vel"+velocity+",acc="+this->acceleration+":dist=0.1\n").c_str());
    cmd = "regbot madd vel=" + velocity + ",acc="+this->acceleration+
              ",edger=0,white=1:dist=5"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    PointToPoint mini_golf;
    UPose targetPose;
    // Adjusting angle 
    targetPose.x = 0;
    targetPose.y = 0;
    targetPose.h = -PI/2; //45 degrees
    mini_golf.goToPoint(&pose,&targetPose,stof(velocity),stof(this->acceleration),0.3);
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.1");
    cmd = "regbot madd vel="+velocity+
              ",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=-0.3,white=1:dist=2,lv<12,xl>10\n";
    bridge.tx(cmd.c_str());
    bridge.tx(("regbot madd vel="+velocity+": dist = 0.05\n").c_str());
    //bridge.tx(("regbot madd vel"+velocity+",acc="+this->acceleration+":dist=0.1\n").c_str());
    //bridge.tx("regbot madd vel=0 : time = 0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    
    // Adjusting angle 
    targetPose.x = 0;
    targetPose.y = 0;
    targetPose.h = PI/2;
    mini_golf.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3);
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    //bridge.tx(("regbot madd vel="+velocity+": dist = 0.1\n").c_str());
    cmd = "regbot madd vel="+velocity+
              ",acc="+this->acceleration+
              ",edger=0,white=1:dist=0.2"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edger=0,white=1:dist=2,lv<12,xl>10\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0 : time = 0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}

void CarouselMission::waitUntilRobot()
{
    int wait_iter = 0;
    while(irsensor.ir2 < 0.7)
    {
        wait_iter++;
        bridge.tx("regbot mclear\n");
        event.clearEvents();
        bridge.tx("regbot madd vel=0 : time = 0.1\n");
        bridge.tx("regbot start\n");
        event.waitForEvent(0);
    }
    if(wait_iter == 0)
    {
        while(irsensor.ir2 > 0.7)
        {
            bridge.tx("regbot mclear\n");
            event.clearEvents();
            bridge.tx("regbot madd vel=0 : time = 0.1\n");
            bridge.tx("regbot start\n");
            event.waitForEvent(0);
        }
        while(irsensor.ir2 < 0.7)
        {
            bridge.tx("regbot mclear\n");
            event.clearEvents();
            bridge.tx("regbot madd vel=0 : time = 0.1\n");
            bridge.tx("regbot start\n");
            event.waitForEvent(0);
        }
    }
}