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
#include "src/MissionManagement.h"
#include "src/uirsensor.h"
#include "src/golf.h"

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
    irsensor.setup();

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
    
    MissionManager mission_manager;
   // cout << "Going to balance" << endl;
    //mission_manager.fromStartToBalance();
    //cout << "Doing golf on seesaw" << endl;
//   mission_manager.ToBalanceShort();
  // mission_manager.doBalance();
    //cout << "Going to Roundabout" << endl;
    //mission_manager.goToRoundabout();
    //cout << "Doing To Roundabout" << endl;
     //mission_manager.doRoundabout();
     //cout << "Doing Carousel" << endl;
     //mission_manager.doCarousel();
     //mission_manager.fromRoundaboutToMiniGolf();
    // cout << "Doing Minigolf" << endl;
    // // mission_manager.GoToMiniGolf();
   // mission_manager.doMiniGolf();
    // cout << "Going to Axe" << endl;
    //mission_manager.fromGolfToAxe();
    // cout << "Doing Axe" << endl;
    //mission_manager.doAxe();
    // cout << "Doing Race track" << endl;
    //mission_manager.doRaceTrack();
    // cout << "Going to goal" << endl;
    //mission_manager.fromRaceTrackToGoal();
  minigolf_run();

    std::cout << "# Robobot mission finished ...\n";
    // remember to close camera
    vision.stop();
    bridge.tx("regbot mute 1\n");  }
  return 0;
}

