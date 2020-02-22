//
// Created by Yan Pujante on 3/14/15.
//

#ifndef _RE_AB_AUDIO_SWITCH_DEVICESTATE_H_
#define _RE_AB_AUDIO_SWITCH_DEVICESTATE_H_

#include <map>
#include "CVSocket.h"
#include "Constants.h"
#include "JBoxProperty.h"
#include "AudioSocket.h"

class DeviceState
{
public:
  DeviceState(char const * iABSwitchPropName,
              char const * iCVInCVSocketName,
              char const * iLedAPropName,
              char const * iLedBPropName);

  virtual void registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag);

  inline TJBox_Bool isCVInConnected() const { return fCVInCVSocket.isConnected(); }
  inline ESwitchState getCVInState() const {
    if(isCVInConnected())
      return fCVInCVSocket.getValue() >= 0 ? kB : kA;
    else
      return kSwitchStateUnknown;
  }

  ESwitchState computeSwitchState(DeviceState const &previousState);

  inline ESwitchState getComputedSwitchState() const { return fComputedSwitchState; }

private:
  // switch (knob) A or B position (
  BooleanJBoxProperty fABKnobJBoxProperty; // boolean false for A, true for B
  inline ESwitchState getKnobState() const { return fABKnobJBoxProperty.getValue() ? kB : kA; }

  // the cv in control socket
  CVInSocket fCVInCVSocket;

  // the LED lights
  BooleanJBoxProperty fLedAJBoxProperty; // ledA (write only)
  BooleanJBoxProperty fLedBJBoxProperty; // ledB (write only)

  // the computed switch state (based on knob position + CV in)
  ESwitchState fComputedSwitchState;
};

class ABAudioSwitchState: public DeviceState
{
public:
  ABAudioSwitchState(): DeviceState("prop_audio_switch", "/cv_inputs/cvInAudio", "prop_audio_ledA", "prop_audio_ledB"),
  fOutputStereoPair("/audio_outputs/audioOutputLeft", "/audio_outputs/audioOutputRight"),
  fInputAStereoPair("/audio_inputs/audioInputLeftA", "/audio_inputs/audioInputRightA"),
  fInputBStereoPair("/audio_inputs/audioInputLeftB", "/audio_inputs/audioInputRightB"),
  fSoundOnJBoxProperty("prop_soundOn"),
  fXFadeSwitchJBoxProperty("prop_xfade_switch")
  {}

  virtual void registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag);

  StereoOutPair fOutputStereoPair;
  StereoInPair fInputAStereoPair;
  StereoInPair fInputBStereoPair;

  BooleanJBoxProperty fSoundOnJBoxProperty; // whether there is sound or not (write only)
  BooleanJBoxProperty fXFadeSwitchJBoxProperty; // boolean false for off, true for on
};

class ABCVSwitchState: public DeviceState
{
public:
  ABCVSwitchState(): DeviceState("prop_cv_switch", "/cv_inputs/cvInCv", "prop_cv_ledA", "prop_cv_ledB"),
    fOutputCVSocket("/cv_outputs/cvOutput"),
    fInputACVSocket("/cv_inputs/cvInputA"),
    fInputBCVSocket("/cv_inputs/cvInputB")
  {
  }

  virtual void registerForUpdate(JBoxPropertyObserver &observer, TJBox_Tag iSwitchPropertyTag);

  CVOutSocket fOutputCVSocket;
  CVInSocket fInputACVSocket;
  CVInSocket fInputBCVSocket;
};


#endif //_RE_AB_AUDIO_SWITCH_DEVICESTATE_H_
