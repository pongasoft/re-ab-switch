//
// Created by Yan Pujante on 3/16/15.
//

#include <Jukebox.h>
#include "AudioSocket.h"

////////////////////////////////
// AudioSocket
////////////////////////////////

AudioSocket::AudioSocket(char const *iSocketPath):
  iSocketRef(JBox_GetMotherboardObjectRef(iSocketPath)), fConnected(iSocketRef, "connected")
{

}

////////////////////////////////
// AudioInSocket
////////////////////////////////

void AudioInSocket::registerForUpdate(JBoxPropertyObserver &observer)
{
  observer.registerForUpdate(fConnected, kJBox_AudioInputConnected);
}

void AudioInSocket::readAudio(TJBox_AudioSample iToBuffer[]) const
{
  TJBox_Value audioValue = JBox_LoadMOMPropertyByTag(iSocketRef, kJBox_AudioInputBuffer);
  JBox_GetDSPBufferData(audioValue, 0, kBatchSize, iToBuffer);
}

////////////////////////////////
// AudioOutSocket
////////////////////////////////

void AudioOutSocket::registerForUpdate(JBoxPropertyObserver &observer)
{
  observer.registerForUpdate(fConnected, kJBox_AudioOutputConnected);
}

void AudioOutSocket::writeAudio(TJBox_AudioSample const iFromBuffer[]) const
{
  TJBox_Value value = JBox_LoadMOMPropertyByTag(iSocketRef, kJBox_AudioOutputBuffer);
  JBox_SetDSPBufferData(value, 0, kBatchSize, iFromBuffer);

}

////////////////////////////////
// StereoPair
////////////////////////////////

void StereoPair::registerForUpdate(JBoxPropertyObserver &observer)
{
  getLeftSocket().registerForUpdate(observer);
  getRightSocket().registerForUpdate(observer);
}

////////////////////////////////
// StereoInPair
////////////////////////////////

AudioSocket &StereoInPair::getLeftSocket()
{
  return fLeftSocket;
}

AudioSocket &StereoInPair::getRightSocket()
{
  return fRightSocket;
}

void StereoInPair::readAudio(TJBox_AudioSample iToLeftBuffer[], TJBox_AudioSample iToRightBuffer[]) const
{
  fLeftSocket.readAudio(iToLeftBuffer);
  fRightSocket.readAudio(iToRightBuffer);
}

////////////////////////////////
// StereoOutPair
////////////////////////////////

AudioSocket &StereoOutPair::getLeftSocket()
{
  return fLeftSocket;
}

AudioSocket &StereoOutPair::getRightSocket()
{
  return fRightSocket;
}

void StereoOutPair::writeAudio(TJBox_AudioSample const iFromLeftBuffer[], TJBox_AudioSample const iFromRightBuffer[]) const
{
  fLeftSocket.writeAudio(iFromLeftBuffer);
  fRightSocket.writeAudio(iFromRightBuffer);
}
