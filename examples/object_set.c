/* EXAMPLE OF SETTING PROPERTIES TOOBJECT */

#include <hmon.h>

int main(void) {
	// Create object
	HMON_Object *object = NULL;

	// Setting proerties
	//
	// Setting proerties just adds properties to the object,
	// but incase the object already has a property it just updates
	//
	// The reason why this exists is, in case we do not know wether
	// an object has a specific property, we just "set" it
	//
	// Instead of (check if object has key) -> (true) : update
	//																			-> (false) : add
	//
	// using this function is faster because hmon_object_add_x() already has
	// a loop to check that, so it's 3 loops (loop to iterate through the object and append)

	hmon_object_add_string(&object, "name", "Hatim");
	hmon_object_add_int(&object, "age", 18);

	hmon_object_print(&object);
	
	// Suppose we somehow don't know what the object has (parsed from a string)
	hmon_object_set_string(&object, "name", "Belahmr");
	hmon_object_set_boolean(&object, "isStudent", true);

	hmon_object_print(&object);
	hmon_object_destroy(&object);
}
