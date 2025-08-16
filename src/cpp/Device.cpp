#include "Device.h"
#include <logging.h>

Device::Device() : fSampleRate{-1}
{
  DLOG_F(INFO, "Device()");

  fCurrentAudioState.registerForUpdate(fJBoxPropertyObserver, kAudioSwitchPropertyTag);
  fCurrentCVState.registerForUpdate(fJBoxPropertyObserver, kCVSwitchPropertyTag);
}

Device::Device(int iSampleRate) :fSampleRate{iSampleRate}
{
  DLOG_F(INFO, "Device(iSampleRate)");

  fCurrentAudioState.registerForUpdate(fJBoxPropertyObserver, kAudioSwitchPropertyTag);
  fCurrentCVState.registerForUpdate(fJBoxPropertyObserver, kCVSwitchPropertyTag);
}

Device::~Device()
{
  DLOG_F(INFO, "~Device()");
}

void Device::renderBatch(TJBox_PropertyDiff const iPropertyDiffs[], TJBox_UInt32 iDiffCount)
{
  fJBoxPropertyObserver.onUpdate(iPropertyDiffs, iDiffCount);

  fAudioSwitch.renderBatch(fPreviousAudioState, fCurrentAudioState);
  fCVSwitch.renderBatch(fPreviousCVState, fCurrentCVState);

  fPreviousAudioState = fCurrentAudioState;
  fPreviousCVState = fCurrentCVState;
}

