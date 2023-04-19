/*  
 * 
 * Copyright © 2022 DTU, 
 * Author:
 * Christian Andersen jcan@dtu.dk
 * 
 * The MIT License (MIT)  https://mit-license.org/
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the “Software”), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies 
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE. */

#include <string>
#include <string.h>
#include "uirsensor.h"
#include "ubridge.h"

// create value
UIrSensor irsensor;


// Bridge class:
void UIrSensor::setup()
{ /// subscribe to pose information
  bridge.tx("regbot:ir subscribe -1\n");
}


bool UIrSensor::decode(char* msg)
{
  bool used = true;
  const char * p1 = strchrnul(msg, ':');
  if (strncmp(p1, ":ir ", 4) == 0)
  { // decode pose message
    // advance to first parameter
    if (strlen(p1) > 4)
      p1 += 4;
    else
      return false;
    // get data
    dataLock.lock();
    // time in seconds
    ir1 = strtof(p1, (char**)&p1); // x
    ir2 = strtof(p1, (char**)&p1); // y
    dataLock.unlock();
  }
  else
    used = false;
  
  
  return used;
}


