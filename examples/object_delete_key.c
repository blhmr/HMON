/* EXAMPLE OF DELETING A KEY-VALUE PAIR FROM OBJECT */

#include <hmon.h>

int main(void) {
  // Create an object
  HMON_Object *account = NULL;

  // Add properties to it
  hmon_object_add_string(&account, "username", "hatim");
  hmon_object_add_string(&account, "password", "123123123");
  hmon_object_add_string(&account, "bio", "I use Arch btw.");

  // Delete property
  printf("Before: \n");
  hmon_object_print(&account);
  hmon_object_delete_key(&account, "bio"); // Yes, but I like Debian more
  hmon_object_print(&account);

  // Destroy
  hmon_object_destroy(&account);
}