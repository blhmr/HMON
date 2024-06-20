/* EXTRA FEATUES */

#include <hmon.h>

int main(void) {
  // Create object
  HMON_Object *object = NULL;

  // Adding properties
  hmon_object_add_string(&object, "name", "Hatim");
  hmon_object_add_int(&object, "age", 18);
  hmon_object_add_string(&object, "country", "Morocco");
  hmon_object_add_boolean(&object, "isStudent", true);

  // Get length
  size_t length = hmon_object_length(&object);
  printf("Object has %zu properties\n", length);

  // Reverse
  hmon_object_reverse(&object);
  hmon_object_print(&object);

  hmon_object_destroy(&object);
}