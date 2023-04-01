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
    targetPose.h = PI/2; //45 degrees
    square_path.goToPoint(&pose,&targetPose,stof(this->velocity),stof(this->acceleration),0.3);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd log=10:time=0.05\n");
    bridge.tx("regbot madd vel=0 : time = 0.3\n");
    bridge.tx(("regbot madd vel="+this->velocity+",tr="+this->radius+":turn=-360\n").c_str());
    bridge.tx("regbot madd vel=0 : time = 0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
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