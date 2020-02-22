//
// Created by Yan Pujante on 3/14/15.
//

#ifndef _RE_AB_AUDIO_SWITCH_CVSOCKET_H_
#define _RE_AB_AUDIO_SWITCH_CVSOCKET_H_

#include "Jukebox.h"
#include "JBoxProperty.h"
#include "JBoxPropertyObserver.h"

class CVSocket
{
public:
  CVSocket(char const *iSocketPath);

  virtual void registerForUpdate(JBoxPropertyObserver &observer) = 0;

  inline TJBox_Bool isConnected() const { return fConnected.getValue(); }

protected:
  TJBox_ObjectRef iSocketRef;
  BooleanJBoxProperty fConnected;
  Float64JBoxProperty fValue;
};

class CVInSocket: public CVSocket
{
public:
  CVInSocket(char const *iSocketPath): CVSocket(iSocketPath) {};

  virtual void registerForUpdate(JBoxPropertyObserver &observer);

  inline TJBox_Float64 getValue() const { return fValue.getValue(); }
};

class CVOutSocket: public CVSocket
{
public:
  CVOutSocket(char const *iSocketPath): CVSocket(iSocketPath) {};

  virtual void registerForUpdate(JBoxPropertyObserver &observer);

  void setValue(TJBox_Float64 value) { fValue.setValue(value).storeValueToMotherboard(); }
};

#endif //_RE_AB_AUDIO_SWITCH_CVSOCKET_H_
