//
//  ABAudioSwitch.h
//  ABAudioSwitch
//
//  Created by Yan Pujante on 1/23/15.
//
//

#pragma once
#ifndef __ABSwitch__ABAudioSwitch__
#define __ABSwitch__ABAudioSwitch__

#include "Jukebox.h"
#include "Constants.h"
#include "ABSwitch.h"

class ABAudioSwitch: public ABSwitch
{
public:
  ABAudioSwitch();

/**
* renderBatch
*/
	void renderBatch(const ABAudioSwitchState &previousState, ABAudioSwitchState &currentState);

  /**
	 * @brief Returns true if there is silence both on the left and right buffers
	 **/
private:
  inline bool isSilent();

	// determine if there is a cross fade to apply
	bool isXFade(const ABAudioSwitchState &previousState, const ABAudioSwitchState &currentState);

	// buffer to read samples (size is kBatchSize)
	TJBox_AudioSample* fLeftAudioBuffer;
	TJBox_AudioSample* fRightAudioBuffer;

	// buffer to read samples for cross fade
	TJBox_AudioSample* fLeftAudioXFadeBuffer;
	TJBox_AudioSample* fRightAudioXFadeBuffer;

	// cross fade function (size is N=kXFadeSizeInSamples)
	TJBox_Float64* fXFadeFunction;

	void xFade(TJBox_Float64* iXFadeFunction);
};

#endif /* defined(__ABSwitch__ABAudioSwitch__) */
