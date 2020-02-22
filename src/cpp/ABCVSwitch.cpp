//
//  ABCVSwitch.cpp
//
//

#include "ABCVSwitch.h"

ABCVSwitch::ABCVSwitch()
{
};

/**
* renderBatch
*/
void ABCVSwitch::renderBatch(const ABCVSwitchState &previousState, ABCVSwitchState &currentState)
{
  ESwitchState currentSwitchState = currentState.computeSwitchState(previousState);

  // no need to do anything if output is not connected...
  if(currentState.fOutputCVSocket.isConnected())
  {
    CVInSocket &vSocket = currentSwitchState == kA ? currentState.fInputACVSocket : currentState.fInputBCVSocket;
    if(vSocket.isConnected())
      currentState.fOutputCVSocket.setValue(vSocket.getValue());
  }
}

