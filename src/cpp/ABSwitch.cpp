#include "ABSwitch.h"

/**
* Constructor
*/
ABSwitch::ABSwitch()
{
  JBOX_TRACE("ABSwitch()");

  // initialize the properties
  fCustomPropertiesRef = JBox_GetMotherboardObjectRef("/custom_properties");
}
