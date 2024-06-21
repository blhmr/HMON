/* EXAMPLE OF GETTING DATA FROM OBJECT */

#include <hmon.h>

int main(void) {
	// Create an object
	HMON_Object *object = NULL;

	// Add properties to object
	hmon_object_add_string(&object, "keyString", "valueString");
	hmon_object_add_int(&object, "keyInt", 10);
	hmon_object_add_boolean(&object, "keyBoolean", false);

	// Get data and print them
	const char *string_value = hmon_object_get_string(&object, "keyString");
	const int int_value = hmon_object_get_int(&object, "keyInt");
	const bool boolean_value = hmon_object_get_boolean(&object, "keyBoolean");

	if (string_value != NULL) {
		printf("{%s, %d, %s}\n", string_value, int_value, boolean_value ? "true" : "false");
		free((void*)string_value);
	}

	hmon_object_destroy(&object);
}
