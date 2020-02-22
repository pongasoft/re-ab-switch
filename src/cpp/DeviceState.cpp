//
// Created by Yan Pujante on 3/14/15.
//

#include <JukeboxTypes.h>
#include "DeviceState.h"


DeviceState::DeviceState(char const *iABSwitchPropName,
                         char const *iCVInCVSocketName,
                         char const *iLedAPropName,
                         char const *iLedBPropName):
  fABKnobJBoxProperty(iABSwitchPropName),
  fCVInCVSocket(iCVInCVSocketName),
  fLedAJBoxProperty(iLedAPropName),
  fLedBJBoxProperty(iLedBPropName),
  fComputedSwitchState(kSwitchStateUnknown)
{
}

void DeviceState::registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag)
{
  observer.registerForUpdate(fABKnobJBoxProperty, iSwitchPropertyTag);
  fCVInCVSocket.registerForUpdate(observer);
}

ESwitchState DeviceState::computeSwitchState(DeviceState const &previousState)
{
  ESwitchState vCurrentKnobState = getKnobState();

//  TJBox_Value values[] = {
//    iPropertyDiff.fPreviousValue,
//    iPropertyDiff.fCurrentValue,
//    JBox_MakeNumber(iPropertyDiff.fPropertyTag),
//    JBox_MakeNumber(iPropertyDiff.fAtFrameIndex),
//    JBox_MakeBoolean(updated)
//  };
//
//  JBOX_TRACEVALUES("DeviceState::computeSwitchState ", values, 5);

  // cv in connected?
  if(isCVInConnected())
  {
    ESwitchState vCurrentReadCvInState = getCVInState();

    // when knob changes => takes precedence
    if(vCurrentKnobState != previousState.getKnobState())
    {
      fComputedSwitchState = vCurrentKnobState;
    }
    else
    {
      if(vCurrentReadCvInState != previousState.getCVInState())
      {
        fComputedSwitchState = vCurrentReadCvInState;
      }
      else
      {
        // otherwise nothing has changed => keep previous value
        fComputedSwitchState = previousState.getComputedSwitchState();
      }
    }
  }
  else
  {
    // cv not connected => value comes from knob
    fComputedSwitchState = vCurrentKnobState;
  }

  // update the led lights corresponding to the state of the switch
  fLedAJBoxProperty.storeValueToMotherboardOnUpdate(fComputedSwitchState == kA, previousState.fLedAJBoxProperty);
  fLedBJBoxProperty.storeValueToMotherboardOnUpdate(fComputedSwitchState == kB, previousState.fLedBJBoxProperty);

  return fComputedSwitchState;

}

void ABCVSwitchState::registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag)
{
  DeviceState::registerForUpdate(observer, iSwitchPropertyTag);
  fOutputCVSocket.registerForUpdate(observer);
  fInputACVSocket.registerForUpdate(observer);
  fInputBCVSocket.registerForUpdate(observer);
}

void ABAudioSwitchState::registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag)
{
  DeviceState::registerForUpdate(observer, iSwitchPropertyTag);
  fOutputStereoPair.registerForUpdate(observer);
  fInputAStereoPair.registerForUpdate(observer);
  fInputBStereoPair.registerForUpdate(observer);
  observer.registerForUpdate(fXFadeSwitchJBoxProperty, kXFadeSwitchPropertyTag);
}
