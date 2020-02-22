#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "JukeboxTypes.h"
#include <stddef.h> // to define size_t

const size_t kBatchSize = 64;
const size_t kXFadeSizeInSamples = kBatchSize;

const TJBox_Tag kAudioSwitchPropertyTag = 100;
const TJBox_Tag kXFadeSwitchPropertyTag = 101;

const TJBox_Tag kCVSwitchPropertyTag = 200;

enum ESwitchState {
  kSwitchStateUnknown, kA, kB
};

#endif
