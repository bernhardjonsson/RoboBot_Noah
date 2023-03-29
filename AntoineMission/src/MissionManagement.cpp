#include "MissionManagement.h"

void MissionManager::fromStartToBalance()
{
    // Setup servo 
    bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=1000,vservo=130:time=1\n");
	bridge.tx("regbot start\n");
    event.waitForEvent(0);

    // First follow line
    float vel = 0.5;
    float acc = 0.8; 
    int level = 12; 
    float distance = 5; 
    bool rightOrLeft = 1;
    FollowLine missionFirstpart(vel, acc, level, distance, rightOrLeft);
    missionFirstpart.runMission();

    //Second follow line (triggered on cross line)
    vel = 0.5;
    rightOrLeft = !rightOrLeft;
    FollowLine missionSecondpart(vel, acc, level, distance, rightOrLeft,1);
    missionSecondpart.runMission();

    // Comment this line if ther is no problem on the ramp (lack of scotch during test)
    missionSecondpart.runMission();

    //Turn to go to balance
    PointToPoint goToBalance;
    UPose targetPose;
    targetPose.x = 0;
    targetPose.y = 0;
    targetPose.h =  1.2217;
    goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

    // Go until golf ball mission start point
    FollowLine missionStartBalance(vel, acc, level, 0.1, rightOrLeft);
    missionStartBalance.runMission();

    targetPose.x = 0.3;
    targetPose.y = 0;
    targetPose.h = 0;
    goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);
}

void MissionManager::doBalance()
{
    // Golf ball mission (Example replace with the real mission)
    bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=-50,vservo=125:time=10\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

    //Follow line until balance point
    bool rightOrLeft = 1;
    float vel = 0.5;
    float acc = 0.8;
    int level = 12;
    float distance = 1.1;
    FollowLine missionEndBalance(vel, acc, level, distance, rightOrLeft);
    missionEndBalance.runMission();

    // Wait until balance is down
    bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd vel=0.0:time=5\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

    distance = 3;
    FollowLine missionEndBalance2(vel, acc, level, distance, rightOrLeft);
    missionEndBalance2.runMission();

}

void MissionManager::goToRoundabout(){
    PointToPoint goToRoundabout;
    UPose target_pose;
    target_pose.x = 0.8;
    target_pose.y = 0;
    target_pose.h = -PI/2 - 10*PI/180; //Adjust angle

    float vel = 0.5;
    float acc = 0.8;
    float turning_speed = 0.3;
    goToRoundabout.goToPoint(&pose,&target_pose,vel,acc,turning_speed);

    target_pose.x = 5;
    target_pose.y = 0;
    target_pose.h = 0;
    goToRoundabout.goToPointUntilLineReached(&target_pose,vel,acc,turning_speed);

    target_pose.x = 0.2;
    target_pose.y = 0;
    target_pose.h = 0;
    goToRoundabout.goToPoint(&pose,&target_pose,vel,acc,turning_speed);

    target_pose.x = 5;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    goToRoundabout.goToPointUntilLineReached(&target_pose,vel,acc,0.2);

    bool rightOrLeft = 0;
    int level = 12;
    float distance = 11.3;
    vel = 0.4;
    FollowLine missionGoToRoundAbout(vel, acc, level, distance, rightOrLeft);
    missionGoToRoundAbout.runMission();

    target_pose.x = 5;
    target_pose.y = 0;
    target_pose.h = -PI/2;
    goToRoundabout.goToPointUntilLineReached(&target_pose,vel,acc,0.2);
}

void MissionManager::doRoundabout()
{
    float vel = 0.5;
    float acc = 0.8;
    float distance = 0.6;
    float irDistance = 0.4;
    float distanceMax = 6.5;
    RoundaboutMission round_about_mission(vel,acc,distance,irDistance,distanceMax);
    round_about_mission.runMissionTest();
}

void MissionManager::doCarousel()
{
    float vel = 0.3;
    float acc = 0.8;
    float radius = 0.375;
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
    cmd = "regbot madd vel=0.3,edgel=-0.3,white=1:dist=2,lv<12,xl>10\n";
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
    cmd = "regbot madd vel=0.3,edgel=0.3,white=1:dist=2,lv<12,xl>10\n";
    bridge.tx(cmd.c_str());
    bridge.tx("regbot madd vel=0.1:dist=0.05\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
    
    target_pose.x = 0;
    target_pose.y = 0;
    target_pose.h = PI/2;
    point_utils.goToPoint(&pose,&target_pose,velocity,acceleration,0.3);
}

void MissionManager::doAxe()
{
    float vel = 1;
    float acc = 0.8;
    float distance = 1;
    float ir_distance = 0.3;
    float max_distance = 1;
    AxeMission axe_mission(vel,acc,distance,ir_distance,max_distance);
    axe_mission.goToAxe();
    axe_mission.runMission();
}

void MissionManager::doRaceTrack()
{
    float vel = 1.2;
    float acc = 0.8;
    RaceTrackMission race_track_mission(vel,acc);
    race_track_mission.runMission();
}

void MissionManager::fromRaceTrackToGoal()
{
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=-110\n");
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
    bridge.tx("regbot madd vel = 0.5,tr=0:turn=-110\n");
    bridge.tx("regbot madd vel = 0:time=0.1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);

    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd vel=0.5,acc=0.8:dist=0.2,lv>12\n");
    bridge.tx("regbot madd vel = 0.5,acc=0.8,edger=0,white=1:dist=0.5,lv<12\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);
}


