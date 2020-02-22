//
//  ABAudioSwitch.cpp
//  ABAudioSwitch
//
//  Created by Yan Pujante on 1/23/15.
//
//

#include "ABAudioSwitch.h"
#include <cmath>

/*
  cross fade constant power
  formula is sqrt(0.5 * (1 + t)) with t[-1, +1]
  a = 2 / N (sampling over N samples (N = 64))
  => t = -1 + (n * a) with n from 0 to N
  => formula is sqrt(0.5 * (1 + t)) = sqrt(0.5 * (1 + -1 + (n * a)) = sqrt(0.5 * a * n) = sqrt(n / N)
  (0..N).each { n -> println "$n -> ${Math.sqrt(n/N)}" }
*/
TJBox_Float64* createConstantPowerXFadeFunction(int size)
{
  TJBox_Float64* vXFadeFunction = new TJBox_Float64[size];
  for(int i = 0; i < size; i++)
  {
    vXFadeFunction[i] = sqrt((double) i / size);
  }
  return vXFadeFunction;
}

/*
  cross fade linear
  formula is 0.5 * (1 + t) with t[-1, +1]
  a = 2 / N (sampling over N samples (N = 64))
  => t = -1 + (n * a) with n from 0 to N
  => formula is 0.5 * (1 + t) = 0.5 * (1 + -1 + n * a) = 0.5 * a * n = n / N
  (0..N).each { n -> println "$n -> ${Math.sqrt(n/N)}" }
*/

TJBox_Float64* createLinearXFadeFunction(int size)
{
  TJBox_Float64* vXFadeFunction = new TJBox_Float64[size];
  for(int i = 0; i < size; i++)
  {
    vXFadeFunction[i] = (double) i / size;
  }
  return vXFadeFunction;
}

ABAudioSwitch::ABAudioSwitch()
{
  JBOX_TRACE("ABAudioSwitch()");

  // initializes the buffers
  fLeftAudioBuffer = new TJBox_AudioSample[kBatchSize];
  fRightAudioBuffer = new TJBox_AudioSample[kBatchSize];
  fLeftAudioXFadeBuffer = new TJBox_AudioSample[kBatchSize];
  fRightAudioXFadeBuffer = new TJBox_AudioSample[kBatchSize];
//  fXFadeFunction = createConstantPowerXFadeFunction(kXFadeSizeInSamples);
  fXFadeFunction = createLinearXFadeFunction(kXFadeSizeInSamples);
};

/**
* renderBatch
*/
void ABAudioSwitch::renderBatch(const ABAudioSwitchState &previousState, ABAudioSwitchState &currentState)
{
//    if(iDiffCount != 0)
//    {
//      for(TJBox_UInt32 i = 0; i < iDiffCount; i++)
//      {
//        TJBox_PropertyDiff iPropertyDiff = iPropertyDiffs[i];
//
//        TJBox_Value values[] = {
//         iPropertyDiff.fPreviousValue,
//         iPropertyDiff.fCurrentValue,
//         JBox_MakeNumber(iPropertyDiff.fPropertyTag),
//         JBox_MakeNumber(iPropertyDiff.fAtFrameIndex)
//        };
//
//        JBOX_TRACEVALUES("ABAudioSwitch.render diff ^0 -> ^1 @^2 [^3]", values, 4);
//      }
//    }

  ESwitchState currentSwitchState = currentState.computeSwitchState(previousState);

  // no need to do anything if output is not connected...
  if(!currentState.fOutputStereoPair.isConnected())
  {
    currentState.fSoundOnJBoxProperty.storeValueToMotherboardOnUpdate(false, previousState.fSoundOnJBoxProperty);
    return;
  }

  StereoInPair &vAudioInput =
    currentSwitchState == kA ? currentState.fInputAStereoPair : currentState.fInputBStereoPair;

  // read audio
  vAudioInput.readAudio(fLeftAudioBuffer, fRightAudioBuffer);

  if (isXFade(previousState, currentState)) {
//    JBOX_TRACE("ABAudioSwitch.render xfading...");

    StereoInPair &vAudioXFadeInput =
      currentSwitchState == kA ? currentState.fInputBStereoPair : currentState.fInputAStereoPair;

    vAudioXFadeInput.readAudio(fLeftAudioXFadeBuffer, fRightAudioXFadeBuffer);
    xFade(fXFadeFunction);
  }

  // detects silence
  bool soundOn = !isSilent();

  currentState.fSoundOnJBoxProperty.storeValueToMotherboardOnUpdate(soundOn, previousState.fSoundOnJBoxProperty);

  // we are not writing any output when silence is detected	
  if (soundOn) {
    // write the output
    currentState.fOutputStereoPair.writeAudio(fLeftAudioBuffer, fRightAudioBuffer);
  }
}

/**
** Code imported from examples.
** 
** @brief		Checks if a buffer is completely silent.
** @details	Note that everything below kJBox_SilentThreshold should be considered silent.
**/
static bool isSilentBuffer(TJBox_AudioSample* iBuffer)
{
  bool silent = true;
  for (size_t i=0; i<kBatchSize; i++) {
    TJBox_AudioSample sampleValue = iBuffer[i];
    if (sampleValue < kJBox_SilentThreshold) {
      sampleValue = -sampleValue;
    }
    if (sampleValue > kJBox_SilentThreshold) {
      silent = false;
      break;
    }
  }
  return silent;
}

/**
** Detects if there is any sound in left or right buffer
*/
bool ABAudioSwitch::isSilent()
{
  return isSilentBuffer(fLeftAudioBuffer) && isSilentBuffer(fRightAudioBuffer);
}

/**
** For a cross fade to happen: the switch state must change, and the option must be selected
*/

bool ABAudioSwitch::isXFade(const ABAudioSwitchState &previousState, const ABAudioSwitchState &currentState)
{
  if(previousState.getComputedSwitchState() == kSwitchStateUnknown ||
     previousState.getComputedSwitchState() == currentState.getComputedSwitchState())
    return false;

  return currentState.fXFadeSwitchJBoxProperty.getValue();
}

/**
* Do the actual cross fade. We assume that kXFadeSizeInSamples is < kBatchSize!
*/
void ABAudioSwitch::xFade(TJBox_Float64* iXFadeFunction)
{
  JBOX_ASSERT(kXFadeSizeInSamples <= kBatchSize);

  TJBox_Float64* vReverseXFadeFunction = &iXFadeFunction[kXFadeSizeInSamples - 1];

  TJBox_AudioSample* vLeftAudioBuffer = fLeftAudioBuffer;
  TJBox_AudioSample* vRightAudioBuffer = fRightAudioBuffer;
  TJBox_AudioSample* vLeftAudioXFadeBuffer = fLeftAudioXFadeBuffer;
  TJBox_AudioSample* vRightAudioXFadeBuffer = fRightAudioXFadeBuffer;

  for(int i = 0; i < kXFadeSizeInSamples; i++, vLeftAudioBuffer++, vRightAudioBuffer++)
  {
    TJBox_Float64 vXFade = *iXFadeFunction++;
    TJBox_Float64 vReverseXFade = *vReverseXFadeFunction--;

    *vLeftAudioBuffer =
      (TJBox_AudioSample) ((*vLeftAudioBuffer * vXFade) + (*vLeftAudioXFadeBuffer++ * vReverseXFade));
    *vRightAudioBuffer =
      (TJBox_AudioSample) ((*vRightAudioBuffer * vXFade) + (*vRightAudioXFadeBuffer++ * vReverseXFade));
  }
}
