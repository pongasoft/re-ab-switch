//
//  ABAudioSwitch.h
//  ABAudioSwitch
//
//  Created by Yan Pujante on 1/23/15.
//
//

#pragma once
#ifndef __ABSwitch__Device__
#define __ABSwitch__Device__

#include "Jukebox.h"
#include "Constants.h"
#include "ABSwitch.h"
#include "ABCVSwitch.h"
#include "ABAudioSwitch.h"
#include "JBoxPropertyObserver.h"

class Device {
public:
  Device();

  /**
  * @brief	Main starting point for rendering audio
  **/
  void renderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

private:
  JBoxPropertyObserver fJBoxPropertyObserver;
  ABAudioSwitchState fPreviousAudioState;
  ABAudioSwitchState fCurrentAudioState;
  ABCVSwitchState fPreviousCVState;
  ABCVSwitchState fCurrentCVState;

  ABAudioSwitch fAudioSwitch;
  ABCVSwitch fCVSwitch;
};

#endif /* defined(__ABSwitch__Device__) */