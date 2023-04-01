#ifndef MISSION_MANAGER_H
#define MISSION_MANAGER_H

#include <iostream>
#include "ubridge.h"
#include "uirsensor.h"
#include "uvision.h"
#include "upose.h"
#include "ucomment.h"
#include "ustate.h"
#include "uplay.h"
#include "uevent.h"
#include "ujoy.h"
#include "FollowLine.h"
#include "AxeMission.h"
#include "PointToPoint.h"
#include "Roundabout.h"
#include "CarouselMission.h"
#include "RaceTrack.h"

class MissionManager
{
    public:
        MissionManager(){};
        void fromStartToBalance();
        void doBalance();
        void goToRoundabout(); //Maybe split this function for the golf ball mission 
        void doRoundabout(); 
        void doCarousel();

        void fromGolfToAxe();
        void doAxe();
        void doRaceTrack();
        void fromRaceTrackToGoal();

        void doMiniGolf();
};

#endif
