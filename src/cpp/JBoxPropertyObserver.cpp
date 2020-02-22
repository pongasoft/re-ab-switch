//
// Created by Yan Pujante on 3/15/15.
//

#include <Jukebox.h>
#include <JukeboxTypes.h>
#include "JBoxPropertyObserver.h"


JBoxPropertyObserver::JBoxPropertyObserver() :
  fProperties(compare)
{
}

void JBoxPropertyObserver::onUpdate(TJBox_PropertyDiff const iPropertyDiffs[], TJBox_UInt32 iDiffCount)
{
  if (iDiffCount != 0) {
    JBoxPropertyMap::const_iterator vNotFound = fProperties.cend();

    for (TJBox_UInt32 i = 0; i < iDiffCount; i++) {
      TJBox_PropertyDiff iPropertyDiff = iPropertyDiffs[i];

      JBoxPropertyKey key(iPropertyDiff.fPropertyRef.fObject, iPropertyDiff.fPropertyTag);
      JBoxPropertyMap::const_iterator iter =
        fProperties.find(key);

      if (iter != vNotFound) {
        iter->second->update(iPropertyDiff);
      }

//      TJBox_Value values[] = {
//        JBox_MakeBoolean(iter != vNotFound),
//        JBox_MakeNumber(iPropertyDiff.fPropertyRef.fObject),
//        iPropertyDiff.fPreviousValue,
//        iPropertyDiff.fCurrentValue
//      };
//
//      JBOX_TRACEVALUES("JBoxPropertyObserver::onUpdate @^1 : ^2 -> ^3 (^0)", values, 4);
//      JBOX_TRACE(iPropertyDiff.fPropertyRef.fKey);

    }
  }
}


void JBoxPropertyObserver::registerForUpdate(JBoxProperty &iJBoxProperty, TJBox_Tag iTag)
{
  JBoxPropertyKey key(iJBoxProperty.fPropertyRef.fObject, iTag);
  JBOX_ASSERT_MESSAGE(fProperties.find(key) == fProperties.cend(), iJBoxProperty.fPropertyRef.fKey);
  fProperties[key] = &iJBoxProperty;
}
