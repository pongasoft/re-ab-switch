//
// Created by Yan Pujante on 3/15/15.
//

#ifndef _RE_AB_AUDIO_SWITCH_JBOXPROPERTYOBVSERVER_H_
#define _RE_AB_AUDIO_SWITCH_JBOXPROPERTYOBVSERVER_H_


#include <map>
#include "JBoxProperty.h"

class JBoxPropertyObserver
{
public:
  JBoxPropertyObserver();

  void onUpdate(TJBox_PropertyDiff const iPropertyDiffs[], TJBox_UInt32 iDiffCount);

  void registerForUpdate(JBoxProperty &iJBoxProperty, TJBox_Tag iTag);

private:
  struct JBoxPropertyKey
  {
    JBoxPropertyKey(TJBox_ObjectRef iObjectRef, TJBox_Tag iTag): fObjectRef(iObjectRef), fTag(iTag) {}

    TJBox_ObjectRef fObjectRef;
    TJBox_Tag fTag;
  };

  typedef std::map<JBoxPropertyKey, JBoxProperty *, bool(*)(JBoxPropertyKey, JBoxPropertyKey)> JBoxPropertyMap;

  static bool compare(JBoxPropertyKey l, JBoxPropertyKey r)
  {
    if(l.fObjectRef == r.fObjectRef)
      return l.fTag < r.fTag;
    else
      return l.fObjectRef < r.fObjectRef;
  }

  JBoxPropertyMap fProperties;
};


#endif //_RE_AB_AUDIO_SWITCH_JBOXPROPERTYOBVSERVER_H_

