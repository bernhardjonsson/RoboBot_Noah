#include "MissionManagement.h"
#include "golf.h"

void MissionManager::fromStartToBalance()
{
    // Setup servo     
    std::cout << "# HOLA ...\n";
    bridge.tx("regbot mclear\n");
    std::cout << "# HOLA ...\n";
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=1000,vservo=130:time=1\n");
    bridge.tx("regbot madd vel=0.3:dist=0.3\n");
	bridge.tx("regbot start\n");
    event.waitForEvent(0);   
    // First follow line
    float vel = 0.25;
    float acc = 0.8; 
    int level = 16; 
    float distance = 5; 
    bool rightOrLeft = 1;
    FollowLine missionFirstpart(vel, acc, level, distance, rightOrLeft);
    missionFirstpart.runMission();

    //Second follow line (triggered on cross line)
    vel = 0.3;
    rightOrLeft = !rightOrLeft;
    distance = 3.5; //Check is distance correct
    FollowLine missionSecondpart(vel, acc, level, distance, rightOrLeft,1);
    missionSecondpart.runMission();

    // Comment this line if ther is no problem on the ramp (lack of scotch during test)
    missionSecondpart.runMission();

    bridge.tx("regbot mclear\n");
	event.clearEvents();
    bridge.tx("regbot madd vel=0.3:dist=0.05\n");
	bridge.tx("regbot start\n"); 
    event.waitForEvent(0);


}

void MissionManager::doBalance()
{
    run_golf_seesaw();

}

void MissionManager::goToRoundabout(){
    PointToPoint goToRoundabout;
    UPose target_pose;
    UPose curr_pose;

    curr_pose.x = 0;
    curr_pose.y = 0;
    curr_pose.h = 0;

    float vel = 0.5;
    float acc = 0.8;
    float turning_speed = 0.3;
    bool rightOrLeft = 1;
    int level = 12;
    float distance = 3; // might need to change value after tests
    
    vel = 0.3;
    bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd log=10: time=0.05\n");
    bridge.tx("regbot madd vel = 0.3,acc = 0.3,edgel=0.2,white=1:dist=0.1,lv>12\n");
	bridge.tx("regbot madd vel=0.3, acc=0.3, edgel=0.2, white=1: tilt>0.1, lv<12\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

    //Safety if line lost
    target_pose.x = 0.1;
    target_pose.y = 0;
    target_pose.h = 0;
    goToRoundabout.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);
    FollowLine missionGoToRoundAbout(vel, acc, level, distance, rightOrLeft);
    missionGoToRoundAbout.runMission();

    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    goToRoundabout.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);
}

void MissionManager::doRoundabout()
{
    float vel = 0.5;
    float acc = 0.8;
    float distance = 0.4;
    float irDistance = 0.4;
    float distanceMax = 6.5;
    RoundaboutMission round_about_mission(vel,acc,distance,irDistance,distanceMax);
    round_about_mission.runMissionTest();
}

void MissionManager::fromRoundaboutToMiniGolf()
{
    float vel = 0.5;
    float acc = 0.8;
    float turning_speed = 0.3;
    bool rightOrLeft = 0;
    int level = 12;
    float distance = 0.6; 
    FollowLine endRoundAbout(vel, acc, level, distance, rightOrLeft);
    endRoundAbout.runMission();

    PointToPoint goToMiniGolf;
    UPose target_pose;
    UPose curr_pose;
    curr_pose.x = 0;
    curr_pose.y = 0;
    curr_pose.h = 0;

    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    goToMiniGolf.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);

    target_pose.x = 0.5;
    target_pose.y = 0;
    target_pose.h = 0;
    goToMiniGolf.goToPointUntilLineReached(&target_pose,vel,acc,0.2);

    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    goToMiniGolf.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);

    distance = 5;
    FollowLine firstPartGoTo(vel, acc, level, distance, rightOrLeft,1);
    firstPartGoTo.runMission();

    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    goToMiniGolf.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);

    FollowLine endPartGoTo(vel, acc, level, distance, rightOrLeft);
    endPartGoTo.runMission();

}

void MissionManager::doCarousel()
{
    float vel = 0.25;
    float acc = 0.8;
    float radius = 0.35;
    CarouselMission carousel_mission(vel,acc,radius);
    carousel_mission.runMission();
}

void MissionManager::fromGolfToAxe()
{
    
    float velocity = 0.5;
    float acceleration = 0.8; 
    string cmd;
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx(("regbot madd vel="+to_string(velocity)+",acc="+to_string(acceleration)+":dist=0.2\n").c_str());
    cmd = "regbot madd vel="+to_string(velocity)+
                ",acc="+to_string(acceleration)+
                ",edger=0,white=1:dist=0.1"+
                ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=-0.3,white=1:dist=0.6,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    waitUntilRobot();

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel="+to_string(velocity)+
                ",acc="+to_string(acceleration)+
                ",edger=0,white=1:dist=0.1"+
                ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=-0.3,white=1:dist=0.6,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    PointToPoint point_utils;
    UPose target_pose;
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);
    /*target_pose.x = 0.1;
    target_pose.y = 0;
    target_pose.h = 0;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);*/

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel="+to_string(velocity)+
              ",acc="+to_string(acceleration)+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edger=0.2,white=1:dist=3,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    // Line lost because of the gap between lines

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel=0.3,acc="+to_string(acceleration)+
              ",edger=0,white=1:dist=0.9"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=0.4,white=1:dist=2,lv<12,xl>10\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0.1:dist=0.05\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);
}

void MissionManager::waitUntilRobot()
{
    int wait_iter = 0;
    while(irsensor.ir2 < 0.5)
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
        while(irsensor.ir2 > 0.5)
        {
            bridge.tx("regbot mclear\n");
            event.clearEvents();
            bridge.tx("regbot madd vel=0 : time = 0.1\n");
            bridge.tx("regbot start\n");
            event.waitForEvent(0);
        }
        while(irsensor.ir2 < 0.5)
        {
            bridge.tx("regbot mclear\n");
            event.clearEvents();
            bridge.tx("regbot madd vel=0 : time = 0.1\n");
            bridge.tx("regbot start\n");
            event.waitForEvent(0);
        }
    }
}

void MissionManager::doAxe()
{
    float vel = 1;
    float acc = 0.8;
    float distance = 0.7;
    float ir_distance = 0.3;
    float max_distance = 1;
    AxeMission axe_mission(vel,acc,distance,ir_distance,max_distance);
    axe_mission.goToAxe();
    axe_mission.runMission();
}

void MissionManager::doRaceTrack()
{
    float vel = 0.8; //1.2
    float acc = 0.8;
    RaceTrackMission race_track_mission(vel,acc);
    race_track_mission.runMission();
}

void MissionManager::fromRaceTrackToGoal()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=-90\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.5,acc=0.8:dist=2,lv>12\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=-120,lv>12\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.3,acc=0.8:dist=0.1,lv>12\n");
    bridge.tx("regbot madd vel = 0.3,acc=0.8,edger=0,white=1:dist=0.5,lv<12\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}

void MissionManager::fromRaceTrackToCarousel()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=-90\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.5,acc=0.8:dist=2,lv>12\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=90\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.5,acc=0.8:dist=0.1,lv>12\n");
    bridge.tx("regbot madd vel=0.5,acc=0.8,edgel=0.2,white=1:dist=7.5,lv<12\n");
    bridge.tx("regbot madd vel = 0.3,acc = 0.3,edgel=0.2,white=1:dist=0.1,lv>12\n");
	bridge.tx("regbot madd vel=0.3, acc=0.3, edgel=0.2, white=1: tilt>0.1, lv<12\n"); 
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    //Safety if line lost
    PointToPoint goToCarousel;
    UPose target_pose;
    UPose curr_pose;

    curr_pose.x = 0;
    curr_pose.y = 0;
    curr_pose.h = 0;

    target_pose.x = 0.1;
    target_pose.y = 0;
    target_pose.h = 0;

    float vel = 0.5;
    float acc = 0.8;
    float turning_speed = 0.3;
    bool rightOrLeft = 1;
    int level = 12;
    float distance = 3;

    goToCarousel.goToPoint(&pose,&target_pose,vel,acc,0.2);
   
    FollowLine missionGoToRoundAbout(vel, acc, level, distance, rightOrLeft);
    missionGoToRoundAbout.runMission();

    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    goToCarousel.goToPoint(&curr_pose,&target_pose,vel,acc,0.2);
    //Run carousel
}

void MissionManager::fromMiniGolfToGoal()
{
    float velocity = 0.5;
    float acceleration = 0.8; 
    string cmd;
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx(("regbot madd vel="+to_string(velocity)+",acc="+to_string(acceleration)+":dist=0.2\n").c_str());
    cmd = "regbot madd vel="+to_string(velocity)+
                ",acc="+to_string(acceleration)+
                ",edger=0,white=1:dist=0.1"+
                ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=-0.3,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    PointToPoint point_utils;
    UPose target_pose;
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);
    target_pose.x = 0.1;
    target_pose.y = 0;
    target_pose.h = 0;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel="+to_string(velocity)+
              ",acc="+to_string(acceleration)+
              ",edger=0,white=1:dist=0.1"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edger=0.2,white=1:dist=2,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    // Line lost because of the gap between lines

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    cmd = "regbot madd vel=0.3,acc="+to_string(acceleration)+
              ",edger=0,white=1:dist=0.5"+
              ",lv>12\n";
    bridge.tx(cmd.c_str());
    cmd = "regbot madd vel=0.3,edgel=0.4,white=1:dist=10,lv<12\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0.1:dist=0.05\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}

void MissionManager::doMiniGolf()
{
    /*for(int run=1; run<=1;run++)
    {
        printf("Performing run: %d of 4\n", run);
        minigolf_run();
    }*/
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.2,tr=0:turn=-180\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

}

void MissionManager::GoToMiniGolf()
{
	PointToPoint goToMiniGolf;
	UPose targetPose;
	float vel = 0.5;
	float acc = 0.8;
	int level = 12;
	float distance = 10;
	bool rightOrLeft = 0;

	FollowLine ToMiniGolf(vel,acc,level,distance,rightOrLeft,1);
	ToMiniGolf.runMission();
}


void MissionManager::ToBalanceShort()
{
    float vel = 0.5;
    float acc = 0.8;
    float level = 12;
    float distance = 5;
    float rightOrLeft=0;
    FollowLine missionSecondpart(vel, acc, level, distance, rightOrLeft,1);
    missionSecondpart.runMission();

}
