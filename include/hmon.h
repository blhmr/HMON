/*

MIT License

Copyright (c) 2024 Hatim Belahmer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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

void hmon_object_update_string(HMON_Object **root, const char *key, const char *new_value);
void hmon_object_update_int(HMON_Object **root, const char *key, int new_value);
void hmon_object_update_float(HMON_Object **root, const char *key, float new_value);
void hmon_object_update_boolean(HMON_Object **root, const char *key, bool new_value);

/* In progress */
char *hmon_object_get_string(HMON_Object **root, const char *key);
int hmon_object_get_int(HMON_Object **root, const char *key);
float hmon_object_get_float(HMON_Object **root, const char *key);
bool hmon_object_get_boolean(HMON_Object **root, const char *key);

// These are faster
void hmon_object_set_string(HMON_Object **root, const char *key, const char *value);
void hmon_object_set_int(HMON_Object **root, const char *key, int value);
void hmon_object_set_float(HMON_Object **root, const char *key, float value);
void hmon_object_set_boolean(HMON_Object **root, const char *key, bool value);

#endif
