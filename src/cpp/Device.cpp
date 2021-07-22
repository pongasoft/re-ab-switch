#include "Device.h"

Device::Device() : fSampleRate{-1}
{
  JBOX_TRACE("Device()");

  fCurrentAudioState.registerForUpdate(fJBoxPropertyObserver, kAudioSwitchPropertyTag);
  fCurrentCVState.registerForUpdate(fJBoxPropertyObserver, kCVSwitchPropertyTag);
}

Device::Device(int iSampleRate) :fSampleRate{iSampleRate}
{
  JBOX_TRACE("Device(iSampleRate)");

  fCurrentAudioState.registerForUpdate(fJBoxPropertyObserver, kAudioSwitchPropertyTag);
  fCurrentCVState.registerForUpdate(fJBoxPropertyObserver, kCVSwitchPropertyTag);
}

Device::~Device()
{
  JBOX_TRACE("~Device()");
}

void Device::renderBatch(TJBox_PropertyDiff const iPropertyDiffs[], TJBox_UInt32 iDiffCount)
{
  fJBoxPropertyObserver.onUpdate(iPropertyDiffs, iDiffCount);

  fAudioSwitch.renderBatch(fPreviousAudioState, fCurrentAudioState);
  fCVSwitch.renderBatch(fPreviousCVState, fCurrentCVState);

  fPreviousAudioState = fCurrentAudioState;
  fPreviousCVState = fCurrentCVState;
}

