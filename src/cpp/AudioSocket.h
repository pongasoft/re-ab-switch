//
// Created by Yan Pujante on 3/16/15.
//

#ifndef _RE_AB_AUDIO_SWITCH_AUDIOSOCKET_H_
#define _RE_AB_AUDIO_SWITCH_AUDIOSOCKET_H_


#include "JBoxPropertyObserver.h"

class AudioSocket
{
public:
  AudioSocket(char const *iSocketPath);

  virtual void registerForUpdate(JBoxPropertyObserver &observer) = 0;

  inline TJBox_Bool isConnected() const { return fConnected.getValue(); }

protected:
  TJBox_ObjectRef iSocketRef;
  BooleanJBoxProperty fConnected;
};

class AudioInSocket: public AudioSocket
{
public:
  AudioInSocket(char const *iSocketPath): AudioSocket(iSocketPath) {}

  virtual void registerForUpdate(JBoxPropertyObserver &observer);

  void readAudio(TJBox_AudioSample iToBuffer[]) const;
};

class AudioOutSocket: public AudioSocket
{
public:
  AudioOutSocket(char const *iSocketPath): AudioSocket(iSocketPath) {}

  virtual void registerForUpdate(JBoxPropertyObserver &observer);

  void writeAudio(TJBox_AudioSample const iFromBuffer[]) const;
};

class StereoPair
{
public:
  virtual void registerForUpdate(JBoxPropertyObserver &observer);

  virtual AudioSocket &getLeftSocket() = 0;
  virtual AudioSocket &getRightSocket() = 0;

  inline TJBox_Bool isConnected() { return getLeftSocket().isConnected() || getRightSocket().isConnected(); }
};

class StereoInPair: public StereoPair
{
public:
  StereoInPair(char const *iLeftSocketPath, char const *iRightSocketPath):
    fLeftSocket(iLeftSocketPath), fRightSocket(iRightSocketPath) { }

  virtual AudioSocket &getLeftSocket();
  virtual AudioSocket &getRightSocket();

  void readAudio(TJBox_AudioSample iToLeftBuffer[], TJBox_AudioSample iToRightBuffer[]) const;

  AudioInSocket fLeftSocket;
  AudioInSocket fRightSocket;
};

class StereoOutPair: public StereoPair
{
public:
  StereoOutPair(char const *iLeftSocketPath, char const *iRightSocketPath):
    fLeftSocket(iLeftSocketPath), fRightSocket(iRightSocketPath) { }

  virtual AudioSocket &getLeftSocket();
  virtual AudioSocket &getRightSocket();

  void writeAudio(TJBox_AudioSample const iFromLeftBuffer[], TJBox_AudioSample const iFromRightBuffer[]) const;

  AudioOutSocket fLeftSocket;
  AudioOutSocket fRightSocket;
};

#endif //_RE_AB_AUDIO_SWITCH_AUDIOSOCKET_H_
