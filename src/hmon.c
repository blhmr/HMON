#include "../include/hmon.h"


// utils
char *__trimmed_string(const char *restrict str) {
	char *result = (char *)malloc(strlen(str) + 1);
	if (result == NULL) return NULL;

	const char *read = str;
	char *write = result;
	bool in_quotes = false;

	while (*read) {
		if (*read == '\'') {
			in_quotes = !in_quotes;
			*write++ = *read;
		} else if (in_quotes || !isspace((unsigned char)*read)) {
			*write++ = *read;
		}
		read++;
	}
	*write = '\0';

	char *shrunk_result = realloc(result, strlen(result) + 1);
	if (shrunk_result == NULL) {
		free((void*)result);
		return NULL;
	}

	return shrunk_result;
}

bool __is_valid_int(const char *restrict str) {
	char *endptr;
	errno = 0;
	long val = strtol(str, &endptr, 10);
	if (errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) return false;
	if (errno != 0 && val == 0) return false;
	if (endptr == str) return false;
	return *endptr == '\0'; 
}

bool __is_valid_float(const char *restrict str) {
	char *endptr;
	errno = 0; 
	double val = strtod(str, &endptr);
	if (errno == ERANGE && (val == HUGE_VAL || val == -HUGE_VAL)) return false;
	if (errno != 0 && val == 0) return false;
	if (endptr == str) return false; 
	return *endptr == '\0';
}

size_t __size_of_object_format(HMON_Object *root) {
	size_t length = 1; // For (
	
	for (HMON_Object *curr = root; curr != NULL; curr = curr->next) {
		length += strlen(curr->key);
		length++; // Either , or )
		switch (curr->type) {
			case HMON_INT:
				length += snprintf(NULL, 0, "%d", curr->value.int_value);
				break;
			case HMON_FLOAT:
				length += snprintf(NULL, 0, "%g", curr->value.float_value);
				break;
			case HMON_BOOLEAN:
				if (curr->value.boolean_value) length += 4; else length += 5;
				break;
			case HMON_STRING:
				length += strlen(curr->value.string_value) + 2;
				break;
			case HMON_UNKOWN: break;
		}
	}

	length++; // Null terminator
	return length;
}

// HMON Functions
bool hmon_object_has_key(HMON_Object **root, const char *restrict key) {
	bool object_has_key = false;
	for (HMON_Object *curr = *root; curr != NULL; curr = curr->next) {
		if (!strcmp(curr->key, key)) {
			object_has_key = true;
			break;
		}
	}
	return object_has_key;
}

size_t hmon_object_length(HMON_Object **root) {
	size_t counter = 0;
	for (HMON_Object *curr = *root; curr != NULL; curr = curr->next) {
		counter++;
	}
	return counter;
}

void hmon_object_print(HMON_Object **root) {
	for (HMON_Object *curr = *root; curr != NULL; curr = curr->next) {
		switch (curr->type) {
			case HMON_STRING:
				printf("(%s='%s') -> ", curr->key, curr->value.string_value);
				break;
			case HMON_INT:
				printf("(%s=%d) -> ", curr->key, curr->value.int_value);
				break;
			case HMON_FLOAT:
				printf("(%s=%g) -> ", curr->key, curr->value.float_value);
				break;
			case HMON_BOOLEAN:
				if (curr->value.boolean_value) printf("(%s=true) -> ", curr->key);
				else printf("(%s=false) -> ", curr->key);
				break;
			default:
				printf("(%s=?) -> ", curr->key);
				break;
		}
	}
	printf("(X)\n");
}

void hmon_object_add_string(HMON_Object **root, const char *restrict key, const char *restrict value) {
	assert(key && value);
	HMON_Object *new_pair = (HMON_Object*) malloc(sizeof(HMON_Object));
	if (new_pair == NULL) {
		exit(-1);
	}
	new_pair->next = NULL;
	new_pair->type = HMON_STRING;
	strcpy(new_pair->key, key);
	strcpy(new_pair->value.string_value, value);

	if (*root == NULL) {
		*root = new_pair;
		return;
	}

	HMON_Object *curr = *root;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_pair;
}

void hmon_object_add_int(HMON_Object **root, const char *restrict key, int value) {
	assert(key);
	HMON_Object *new_pair = (HMON_Object*) malloc(sizeof(HMON_Object));
	if (new_pair == NULL) {
		exit(-1);
	}
	new_pair->next = NULL;
	new_pair->type = HMON_INT;
	strcpy(new_pair->key, key);
	new_pair->value.int_value = value;

	if (*root == NULL) {
		*root = new_pair;
		return;
	}

	HMON_Object *curr = *root;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_pair;
}

void hmon_object_add_float(HMON_Object **root, const char *restrict key, float value) {
	assert(key);
	HMON_Object *new_pair = (HMON_Object*) malloc(sizeof(HMON_Object));
	if (new_pair == NULL) {
		exit(-1);
	}
	new_pair->next = NULL;
	new_pair->type = HMON_FLOAT;
	strcpy(new_pair->key, key);
	new_pair->value.float_value = value;

	if (*root == NULL) {
		*root = new_pair;
		return;
	}

	HMON_Object *curr = *root;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_pair;
}

void hmon_object_add_boolean(HMON_Object **root, const char *restrict key, bool value) {
	assert(key);
	HMON_Object *new_pair = (HMON_Object*) malloc(sizeof(HMON_Object));
	if (new_pair == NULL) {
		exit(-1);
	}
	new_pair->next = NULL;
	new_pair->type = HMON_BOOLEAN;
	strcpy(new_pair->key, key);
	new_pair->value.boolean_value = value;

	if (*root == NULL) {
		*root = new_pair;
		return;
	}

	HMON_Object *curr = *root;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = new_pair;
}

void hmon_object_destroy(HMON_Object **root) {
	HMON_Object *curr = *root;
	while (curr != NULL) {
		HMON_Object *aux = curr;
		curr = curr->next;
		free((void*)aux);
	}
	*root = NULL;
}

void hmon_object_delete_key(HMON_Object **root, const char *restrict key) {
	assert(key);
	if (*root == NULL) {
		return;
	}

	if (!strcmp((*root)->key, key)) {
		HMON_Object *pair_to_remove = *root;
		*root = (*root)->next;
		free((void*)pair_to_remove);
		return;
	}

	for (HMON_Object *curr = *root; curr->next != NULL; curr = curr->next) {
		if (!strcmp(curr->next->key, key)) {
			HMON_Object *pair_to_remove;
			curr->next = curr->next->next;
			free((void*)pair_to_remove);
			return;
		}
	}
}

void hmon_object_reverse(HMON_Object **root) {
	HMON_Object *prev = NULL;
	HMON_Object *curr = *root;

	while (curr != NULL) {
		HMON_Object *next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*root = prev;
}

char *hmon_object_format(HMON_Object **root) {
	char *output = NULL;

	if (*root != NULL) {
		size_t length = __size_of_object_format(*root);
		output = (char*) malloc(sizeof(char) * length + 1);
		strcat(output, "(");
		
		HMON_Object *curr = *root;
		while (curr != NULL) {
			strcat(output, curr->key);
			strcat(output, "=");
			char numeric_string[50];
			switch (curr->type) {
				case HMON_INT:
					sprintf(numeric_string, "%d", curr->value.int_value);
					numeric_string[strlen(numeric_string)] = '\0';
					strcat(output, numeric_string);
					break;
				case HMON_FLOAT:
					sprintf(numeric_string, "%g", curr->value.float_value);
					numeric_string[strlen(numeric_string)] = '\0';
					strcat(output, numeric_string);
					break;
				case HMON_BOOLEAN:
					if (curr->value.boolean_value) {
						strcat(output, "true");
					} else {
						strcat(output, "false");
					}
					break;
				case HMON_STRING:
					strcat(output, "'");
					strcat(output, curr->value.string_value);
					strcat(output, "'");
					break;
				case HMON_UNKOWN: break;
			}
			if (curr->next == NULL) {
				strcat(output, ")");
			}
			else {
				strcat(output, ", ");
			}
			curr = curr->next;
		}
	}

	return output;
}

void hmon_parse_string_object(HMON_Object **root, const char *restrict input) {
	char *trimmed = __trimmed_string(input);
	if (trimmed == NULL) {
		return;
	}

	if (trimmed[0] != '(' || trimmed[strlen(trimmed) - 1] != ')') {
		return;
	}
	else {
		char *ptr = trimmed;
		ptr++; // Skip (
		while (*ptr != '\0') {
			char key[HMON_MAX_KEY_LEN], value[HMON_MAX_VALUE_STRING];
			HMON_Type type = HMON_UNKOWN;

			const char *key_begin = ptr;
			while (*ptr != '=') ptr++;
			const char *key_end = ptr;
			strncpy(key, key_begin, key_end - key_begin);
			key[key_end - key_begin] = '\0';

			ptr++; // Skip =

			if (*ptr == '\'') {
				type = HMON_STRING;
				ptr++; // Skip '
				const char *string_value_begin = ptr;
				while (*ptr != '\'' && *ptr != '\0') ptr++;
				const char *string_value_end = ptr;
				strncpy(value, string_value_begin, string_value_end - string_value_begin);
				value[string_value_end - string_value_begin] = '\0';
				ptr++; // Skip '
			}
			else {
				const char *value_begin = ptr;
				while (*ptr != ',' && *ptr != '\0') ptr++;
				const char *value_end = ptr;
				strncpy(value, value_begin, value_end - value_begin);
				value[value_end - value_begin] = '\0';
			}

			if (type == HMON_STRING) {
				hmon_object_add_string(root, key, value);
			}
			else {
				if (__is_valid_int(value)) {
					hmon_object_add_int(root, key, atoi(value));
				}
				else if (__is_valid_float(value)) {
					hmon_object_add_float(root, key, strtod(value, NULL));
				}
				else if (!strcmp(value, "true")) {
					hmon_object_add_boolean(root, key, true);
				}
				else if (!strcmp(value, "false")) {
					hmon_object_add_boolean(root, key, false);
				}
			}

			ptr++;
			if (*ptr == ')') break;
		}
	}

	free((void*)trimmed);
}