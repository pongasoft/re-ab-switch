//
//  ABCVSwitch.h
//  ABCVSwitch
//

#pragma once
#ifndef __ABSwitch__ABCVSwitch__
#define __ABSwitch__ABCVSwitch__

#include "Jukebox.h"
#include "Constants.h"
#include "ABSwitch.h"

class ABCVSwitch: public ABSwitch
{
public:
  ABCVSwitch();

/**
* renderBatch
*/
  void renderBatch(const ABCVSwitchState &previousState, ABCVSwitchState &currentState);
};

#endif /* defined(__ABSwitch__ABCVSwitch__) */
