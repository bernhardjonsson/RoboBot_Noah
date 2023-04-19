#ifndef RACETRACK_H
#define RACETRACK_H

#include "ubridge.h"
#include "uevent.h"
#include "uirsensor.h"
#include "PointToPoint.h"

class RaceTrackMission
{
    private:
    string velocity;
    string acceleration;

    public:
    RaceTrackMission(float vel, float acc);
    void runMission();
};
#endif
