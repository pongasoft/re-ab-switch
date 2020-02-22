//
// Created by Yan Pujante on 3/15/15.
//

#ifndef _RE_AB_AUDIO_SWITCH_JBOXPROPERTY_H_
#define _RE_AB_AUDIO_SWITCH_JBOXPROPERTY_H_


#include <JukeboxTypes.h>
#include "Constants.h"

class JBoxProperty
{
public:
  JBoxProperty(TJBox_ObjectRef parentRef, char const *iPropertyName);
  JBoxProperty(char const *iPropertyName);

  void update(const TJBox_PropertyDiff &iPropertyDiff);
  void loadValueFromMotherboard();
  void storeValueToMotherboard();

  JBoxProperty &operator=(const JBoxProperty &other);

  TJBox_PropertyRef const fPropertyRef;

protected:
  virtual void setJBoxValue(TJBox_Value value) = 0;
  virtual TJBox_Value getJBoxValue() = 0;

};

class BooleanJBoxProperty : public JBoxProperty
{
public:
  inline BooleanJBoxProperty(TJBox_ObjectRef parentRef, char const *iPropertyName):
    JBoxProperty(parentRef, iPropertyName), fValue(false)
  { }
  inline BooleanJBoxProperty(char const *iPropertyName):
    JBoxProperty(iPropertyName), fValue(false)
  { }

  inline TJBox_Bool getValue() const { return fValue; }
  inline BooleanJBoxProperty &setValue(TJBox_Bool iValue) { fValue = iValue; return *this; }
  void storeValueToMotherboardOnUpdate(TJBox_Bool iValue, BooleanJBoxProperty const &previous);

private:
  TJBox_Bool fValue;

  virtual void setJBoxValue(TJBox_Value value);
  virtual TJBox_Value getJBoxValue();
};

class Float64JBoxProperty : public JBoxProperty
{
public:
  inline Float64JBoxProperty(TJBox_ObjectRef parentRef, char const *iPropertyName):
    JBoxProperty(parentRef, iPropertyName), fValue(0)
  { }
  inline Float64JBoxProperty(char const *iPropertyName):
    JBoxProperty(iPropertyName), fValue(0)
  { }

  inline TJBox_Float64 getValue() const { return fValue; }
  inline Float64JBoxProperty &setValue(TJBox_Float64 iValue) { fValue = iValue; return *this; }

private:
  TJBox_Float64 fValue;

  virtual void setJBoxValue(TJBox_Value value);
  virtual TJBox_Value getJBoxValue();
};

#endif //_RE_AB_AUDIO_SWITCH_JBOXPROPERTY_H_
