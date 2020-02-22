//
// Created by Yan Pujante on 3/14/15.
//

#include <JukeboxTypes.h>
#include "CVSocket.h"

CVSocket::CVSocket(char const *iSocketPath):
  iSocketRef(JBox_GetMotherboardObjectRef(iSocketPath)), fConnected(iSocketRef, "connected"), fValue(iSocketRef, "value")
{
}

void CVInSocket::registerForUpdate(JBoxPropertyObserver &observer)
{
  observer.registerForUpdate(fConnected, kJBox_CVInputConnected);
  observer.registerForUpdate(fValue, kJBox_CVInputValue);
}

void CVOutSocket::registerForUpdate(JBoxPropertyObserver &observer)
{
  observer.registerForUpdate(fConnected, kJBox_CVOutputConnected);
}
