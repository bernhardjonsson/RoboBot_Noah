#ifndef FOLLOW_LINE
#define FOLLOW_LINE


#include "ubridge.h"
#include "uevent.h"

using namespace std;
class FollowLine
{
private:
    string velocity;
    string acceleration;
    string level;
    string distance;
    bool rightOrLeft;
    bool stopOnCrossLine = 0;
public:
    FollowLine(float vel, float acc,
            int level,float distance,bool rightOrLeft);
    FollowLine(float vel, float acc,
            int level,float distance,bool rightOrLeft,
            bool stopOnCrossLine);
    ~FollowLine();
    void runMission();
};



#endif