//
//  ABSwitch.h
//
//

#pragma once
#ifndef __ABSwitch__ABSwitch__
#define __ABSwitch__ABSwitch__

#include "Jukebox.h"
#include "Constants.h"
#include "CVSocket.h"
#include "DeviceState.h"

class ABSwitch
{
public:
  ABSwitch();

protected:

  TJBox_PropertyRef makePropertyRef(const TJBox_ObjectName iMOMPath, const TJBox_PropertyKey iKey)
  {
    TJBox_ObjectRef vObjectRef = JBox_GetMotherboardObjectRef(iMOMPath);
    return JBox_MakePropertyRef(vObjectRef, iKey);
  }

  // references to properties
protected:
  TJBox_ObjectRef fCustomPropertiesRef;
};

#endif /* defined(__ABSwitch__ABSwitch__) */
