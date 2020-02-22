//
// Created by Yan Pujante on 3/15/15.
//

#include <Jukebox.h>
#include <JukeboxTypes.h>
#include "JBoxProperty.h"

TJBox_ObjectRef getCustomPropertiesRef()
{
  return JBox_GetMotherboardObjectRef("/custom_properties");
}

////////////////////////////////
// JBoxProperty
////////////////////////////////

JBoxProperty &JBoxProperty::operator=(const JBoxProperty &other)
{
  JBOX_ASSERT_MESSAGE(JBox_IsReferencingSameProperty(other.fPropertyRef, fPropertyRef), "mismatch object!");

  // nothing to do in base class
  return *this;
}

JBoxProperty::JBoxProperty(TJBox_ObjectRef parentRef, char const *iPropertyName):
  fPropertyRef(JBox_MakePropertyRef(parentRef, iPropertyName))
{
}

JBoxProperty::JBoxProperty(char const *iPropertyName):
  fPropertyRef(JBox_MakePropertyRef(getCustomPropertiesRef(), iPropertyName))
{
}

void JBoxProperty::update(const TJBox_PropertyDiff &iPropertyDiff)
{
  JBOX_ASSERT_MESSAGE(JBox_IsReferencingSameProperty(iPropertyDiff.fPropertyRef, fPropertyRef), "mismatch object!");
  setJBoxValue(iPropertyDiff.fCurrentValue);
}

void JBoxProperty::loadValueFromMotherboard()
{
  setJBoxValue(JBox_LoadMOMProperty(fPropertyRef));
}

void JBoxProperty::storeValueToMotherboard()
{
  JBox_StoreMOMProperty(fPropertyRef, getJBoxValue());
}

////////////////////////////////
// JBoxBooleanProperty
////////////////////////////////

void BooleanJBoxProperty::setJBoxValue(TJBox_Value value)
{
  fValue = JBox_GetBoolean(value);
}

TJBox_Value BooleanJBoxProperty::getJBoxValue()
{
  return JBox_MakeBoolean(fValue);
}

void BooleanJBoxProperty::storeValueToMotherboardOnUpdate(TJBox_Bool iValue, BooleanJBoxProperty const &previous)
{
  setValue(iValue);
  if(getValue() != previous.getValue())
    storeValueToMotherboard();
}

////////////////////////////////
// JBoxFloat64Property
////////////////////////////////

void Float64JBoxProperty::setJBoxValue(TJBox_Value value)
{
  fValue = JBox_GetNumber(value);
}

TJBox_Value Float64JBoxProperty::getJBoxValue()
{
  return JBox_MakeNumber(fValue);
}

