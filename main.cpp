/*  
 
 Copyright © 2022 DTU, Christian Andersen jcan@dtu.dk
 
 The MIT License (MIT)  https://mit-license.org/
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the “Software”), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
 is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies 
 or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 THE SOFTWARE. */


#include <iostream>
#include "src/ubridge.h"
#include "src/uvision.h"
#include "src/upose.h"
#include "src/ucomment.h"
#include "src/ustate.h"
#include "src/uplay.h"
#include "src/uevent.h"
#include "src/ujoy.h"

// to avoid writing std:: 
using namespace std;


bool setup(int argc, char **argv)
{ // check for command line parameters
  for (int i = 1; i < argc; i++)
  { // check for command line parameters
    // for process debug
    if (strcmp(argv[i], "help") == 0)
    { 
      printf("-----\n# User mission command line help\n");
      printf("# usage:\n#   ./user_mission [help] [ball] [show] [aruco] [videoX]\n-----\n");
      return false;
    }
  }
  // connect to robot hardware using bridge
  bridge.setup("127.0.0.1", "24001", argc, argv);
  if (true or bridge.connected)
  {  /// call setup for data structures
    pose.setup();
    comment.setup();
    state.setup();
    vision.setup(argc, argv);
    event.setup();
    joy.setup();
    printf("# Setup finished OK\n");
  }
  else
	{
    printf("# Setup failed\n");
 		sound.say("me?... I am a depressed robot.", 0.1);
	}
		//   while (sound.isSaying())
//     usleep(100000);
  // a bit of background music
  //sound.play("/home/local/Music/music.mp3", 0.05);
  return true;
}

void step1()
{
  sound.say(". Step one.", 0.3);
  // remove old mission
  bridge.tx("regbot mclear\n");
  // clear events received from last mission
  event.clearEvents();
  // add mission lines
  bridge.tx("regbot madd vel=0.2:time=1\n");
  bridge.tx("regbot madd tr=0.1:time=1,turn=-90\n");
  bridge.tx("regbot madd :time=1\n");
  // start this mission
  bridge.tx("regbot start\n");
  // wait until finished
  //
  cout << "Waiting for step 1 to finish (event 0 is send, when mission is finished)\n";
  event.waitForEvent(0);
//   sound.say(". Step one finished.");
}

void step2()
{
//   sound.say(". Step two. Press button two for right, button three for left", 0.3);
  bool go_left = true;
  while (true)
  { // wait for decision (button 2 (right) or 3 (left))
    if (joy.button(2))
    {
      go_left = false;
      sound.say(". OK. Going right.", 0.3);
      break;
    }
    else if (joy.button(3))
    {
      go_left = true;
      sound.say(". OK. Going left.", 0.3);
      break;
    }
    else // wait
      usleep(5000);
  }
  // remove old mission
  bridge.tx("regbot mclear\n");
  // clear events received from last mission
  event.clearEvents();
  // add mission lines
  if (go_left)
    bridge.tx("regbot madd vel=0.2,tr=0.1:turn=90\n");
  else
    bridge.tx("regbot madd vel=0.2,tr=0.1:turn=-90\n");
  // drive a bit straight for correct end heading
  bridge.tx("regbot madd :dist=0.2\n"); 
  // start this mission
  bridge.tx("regbot start\n");
  // wait until finished
  cout << "Waiting for step 1 to finish (event 0 is send, when mission is finished)\n";
  event.waitForEvent(0);
  sound.say(". Step two finished.");
}

int main(int argc, char **argv) 
{
  if (setup(argc, argv))
  { // start mission
  /*cout << irsensor.ir1 << endl;
  cout << irsensor.ir2 << endl;
  float vel = 0.3;
  float acc = 0.8; 
  int level = 4; 
  float distance = 1; 
  bool rightOrLeft = 1;
    FollowLine missiontest(vel, acc, level, distance, rightOrLeft);
    missiontest.runMission();
  */
   /*if (irsensor.ir2 >= 0.5){
      bridge.tx("regbot mclear\n");
      bridge.tx("regbot madd log=10:time = 0.05\n");
      bridge.tx("regbot madd vel=0.3:ir2 < 0.25\n");
      bridge.tx("regbot madd vel=0 : time = 0.5\n");
      bridge.tx("regbot start\n");
    }*/
   /* float vel = 0.3;
    float acc = 0.8; 
    float distance = 1; 
    float irDistance = 0.3;
    float maxDistance = 1.5;
    AxeMission axeMissionTest(vel,acc,distance,irDistance,maxDistance);
    axeMissionTest.runMission();*/
  /*
    PointToPoint goToTest;
    UPose targetPose;
    targetPose.x = 1.5;
    targetPose.y = 0;
    targetPose.h = -PI/2;

    float speed = 1.5;
    float acc = 0.8;
    float turnSpeed = 0.5;
    goToTest.goToPoint(&pose,&targetPose,speed,acc,turnSpeed);
    
    targetPose.x = 1.5;
    targetPose.y = 0;
    targetPose.h = -PI/2;
    goToTest.goToPoint(&pose,&targetPose,speed,acc,turnSpeed);

    targetPose.x = 1.5;
    targetPose.y = 0;
    targetPose.h = -PI/2;
    goToTest.goToPoint(&pose,&targetPose,speed,acc,turnSpeed);

    targetPose.x = 1.5;
    targetPose.y = 0;
    targetPose.h = -PI/2;
    goToTest.goToPoint(&pose,&targetPose,speed,acc,turnSpeed);

    */
  bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=1000,vservo=130:time=5\n");
	bridge.tx("regbot start\n");
  event.waitForEvent(0);

   float vel = 0.5;
  float acc = 0.8; 
  int level = 12; 
  float distance = 5; 
  bool rightOrLeft = 1;
  FollowLine missionFirstpart(vel, acc, level, distance, rightOrLeft);
  missionFirstpart.runMission();

  vel = 0.5;
  distance = 10;
  rightOrLeft = 0;
  FollowLine missionSecondpart(vel, acc, level, distance, rightOrLeft,1);
  missionSecondpart.runMission();

  PointToPoint goToBalance;
  UPose targetPose;
  targetPose.x = 0;
  targetPose.y = 0;
  targetPose.h =  1.2217;
  goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);
  FollowLine missionStartBalance(vel, acc, level, 0.1, rightOrLeft);
  missionStartBalance.runMission();

  targetPose.x = 0.3;
  targetPose.y = 0;
  targetPose.h = 0;
  goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);
  // Golf ball mission
  bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd servo=1,pservo=-50,vservo=125:time=10\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);
  // ENd 
  rightOrLeft = 1;
  vel = 0.3;
  FollowLine missionEndBalance(vel, acc, level, 1.5, rightOrLeft);
  missionEndBalance.runMission();

  // Wait until balance is down
   bridge.tx("regbot mclear\n");
	event.clearEvents();
	bridge.tx("regbot madd vel=0.0:time=5\n");
	bridge.tx("regbot start\n");
	event.waitForEvent(0);

  FollowLine missionEndBalance2(vel, acc, level, 1, rightOrLeft);
  missionEndBalance2.runMission();

  targetPose.x = 1;
  targetPose.y = 0;
  targetPose.h = -PI/2;
  goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

  targetPose.x = 5;
  targetPose.y = 0;
  targetPose.h = 0;
  goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);

  targetPose.x = 0.2;
  targetPose.y = 0;
  targetPose.h = 0;
  goToBalance.goToPoint(&pose,&targetPose,vel,acc,0.3);

  targetPose.x = 5;
  targetPose.y = 0;
  targetPose.h = -1.2217;
  goToBalance.goToPointUntilLineReached(&targetPose,vel,acc,0.2);

  rightOrLeft = 0;
  vel = 0.5;
  FollowLine missionGoToRoundAbout(vel, acc, level, 12, rightOrLeft);
  missionGoToRoundAbout.runMission();

  }
  return 0;
}

