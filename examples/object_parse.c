/* EXAMPLE OF PARSING STRING TO OBJECT */

#include <hmon.h>

int main(void) {
  // Create object
  HMON_Object *object = NULL;

  // Parse string to object
  hmon_parse_string_object(&object, "(username = 'Hatim', password = 'Somepass123', email = 'hatim.withred@gmail.com')");

  hmon_object_print(&object);
  hmon_object_destroy(&object);
}