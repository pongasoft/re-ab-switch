#include "Device.h"

Device::Device()
{
  fCurrentAudioState.registerForUpdate(fJBoxPropertyObserver, kAudioSwitchPropertyTag);
  fCurrentCVState.registerForUpdate(fJBoxPropertyObserver, kCVSwitchPropertyTag);
}

void Device::renderBatch(TJBox_PropertyDiff const iPropertyDiffs[], TJBox_UInt32 iDiffCount)
{
  fJBoxPropertyObserver.onUpdate(iPropertyDiffs, iDiffCount);

  fAudioSwitch.renderBatch(fPreviousAudioState, fCurrentAudioState);
  fCVSwitch.renderBatch(fPreviousCVState, fCurrentCVState);

  fPreviousAudioState = fCurrentAudioState;
  fPreviousCVState = fCurrentCVState;
}
