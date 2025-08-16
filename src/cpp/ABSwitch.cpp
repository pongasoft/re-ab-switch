#include "ABSwitch.h"
#include <logging.h>

/**
* Constructor
*/
ABSwitch::ABSwitch()
{
  DLOG_F(INFO, "ABSwitch()");

  // initialize the properties
  fCustomPropertiesRef = JBox_GetMotherboardObjectRef("/custom_properties");
}
