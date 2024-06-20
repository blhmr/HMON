/* EXAMPLE OF FORMATTING AN OBJECT INTO A STRING */

#include <hmon.h>

int main(void) {
  // Create an object
  HMON_Object *server = NULL;

  // Adding properties
  hmon_object_add_string(&server, "HOST", "127.0.0.1");
  hmon_object_add_int(&server, "PORT", 8080);
  hmon_object_add_string(&server, "TYPE", "IPV4");
  hmon_object_add_int(&server, "MAX_CONNECTIONS", 10);

  // Format object
  char *format_server = hmon_object_format(&server);
  if (format_server != NULL) {
    printf("FORMAT: %s\n", format_server);

    /* Do stuffs with the formatted string */

    free((void*)format_server);
  }
  else {
    fprintf(stderr, "Could not format object\n");
    return -1;
  }

  // Destroy object
  hmon_object_destroy(&server);
}