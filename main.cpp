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
#include<cmath>
#include <string>

#include "src/ubridge.h"
#include "src/uvision.h"
#include "src/upose.h"
#include "src/ucomment.h"
#include "src/ustate.h"
#include "src/uplay.h"
#include "src/uevent.h"
#include "src/ujoy.h"
#include "src/PointToPoint.h"
#include "src/golf.h"
#include "src/FollowLine.h"

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

    // move arm to initial position
    bridge.tx("regbot mclear\n");
    event.clearEvents();
    bridge.tx("regbot madd servo=1,pservo=1000,vservo=0:time=1\n");
    bridge.tx("regbot start\n");
    event.waitForEvent(0);    

    printf("# Setup finished OK\n");
  }
  else
	{
    printf("# Setup failed\n");
    return false;
	}
  return true;
}

int main(int argc, char **argv) 
{
  if (setup(argc, argv))
  { // start mission
    std::cout << "# Robobot mission starting ...\n";
    PointToPoint goToBalance;
    UPose targetPose;
    float vel = 0.5;
    float acc = 0.8; 
    int level = 12; 
    float distance = 5; 
    bool rightOrLeft = 0;
    vel = 0.5;
    distance = 10;
    FollowLine missionSecondpart(vel, acc, level, distance, rightOrLeft,1);
    missionSecondpart.runMission();     
  
    run_golf_seesaw();
	//run_mini_golf();
	//minigolf_test();
	
    std::cout << "# Robobot mission finished ...\n";



    // remember to close camera
    vision.stop();
    bridge.tx("regbot mute 1\n");
  }
  return 0;
}
