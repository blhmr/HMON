/* EXAMPLE OF CREATING AN OBJECT AND ADD KEY-VALUE PAIRS TO IT */

#include <hmon.h>

int main(void) {
  // Creating empty object
  HMON_Object *object = NULL;

  // Adding properties to object (key-value pairs)
  hmon_object_add_string(&object, "stringValue", "This is a string");
  hmon_object_add_int(&object, "intValue", 2006);
  hmon_object_add_float(&object, "floatValue", 3.14);
  hmon_object_add_boolean(&object, "booleanValue", true);

/*
  These are all the datatypes you can add to an object
  (basically everything you need for a minimal object notation)
*/

  // Visualize object
  hmon_object_print(&object);

  // Don't forget to clean up !
  hmon_object_destroy(&object);
}
