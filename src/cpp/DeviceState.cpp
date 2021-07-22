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
  fComputedSwitchState = isCVInConnected() ? getCVInState() : getKnobState();

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
