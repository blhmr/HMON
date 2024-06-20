/* EXAMPLE OF UPDATING PROPERTY OF OBJECT */

#include <hmon.h>

int main(void) {
  // Create object
  HMON_Object *car = NULL;

  // Add properties
  hmon_object_add_string(&car, "brand", "Mercedes");
  hmon_object_add_string(&car, "type", "CLR GTR");
  hmon_object_add_string(&car, "color", "Black");
  hmon_object_add_string(&car, "engine", "V12");
  hmon_object_add_int(&car, "horsepower", 600);
  hmon_object_add_float(&car, "topspeed", 370.0);
  hmon_object_add_float(&car, "price", 1500000.0);

  // Print object
  hmon_object_print(&car);

  // Update object
  hmon_object_update_float(&car, "price", 2000000.0);
  hmon_object_print(&car);
  hmon_object_destroy(&car);
}