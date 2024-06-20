#ifndef __HMON_H__
#define __HMON_H__

#ifndef HMON_MAX_KEY_LEN
#define HMON_MAX_KEY_LEN 50
#endif

#ifndef HMON_MAX_VALUE_STRING
#define HMON_MAX_VALUE_STRING 50
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

typedef enum HMON_Type {
	HMON_STRING,
	HMON_INT,
	HMON_FLOAT,
	HMON_BOOLEAN,
	HMON_UNKOWN,
} HMON_Type;

typedef struct HMON_Object {
	char key[HMON_MAX_KEY_LEN + 1];
	HMON_Type type;
	union {
		int int_value;
		float float_value;
		bool boolean_value;
		char string_value[HMON_MAX_VALUE_STRING + 1];
	} value;
	struct HMON_Object *next;
} HMON_Object;

/* Function prototypes */
bool hmon_object_has_key(HMON_Object **root, const char *key);
void hmon_object_print(HMON_Object **root);
size_t hmon_object_length(HMON_Object **root);

void hmon_object_add_string(HMON_Object **root, const char *key, const char *value);
void hmon_object_add_int(HMON_Object **root, const char *key, int value);
void hmon_object_add_float(HMON_Object **root, const char *key, float value);
void hmon_object_add_boolean(HMON_Object **root, const char *key, bool value);

void hmon_object_destroy(HMON_Object **root);
void hmon_object_delete_key(HMON_Object **root, const char *key);
void hmon_object_reverse(HMON_Object **root);

char *hmon_object_format(HMON_Object **root);

void hmon_parse_string_object(HMON_Object **root, const char *input);

#endif
