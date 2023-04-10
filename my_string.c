#include "my_string.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *string_error_code_str(string_error_codes_t code) {
	switch (code) {
		case STRING_NONE:
			return "No error.";
		case STRING_MALLOC_ERROR:
			return "There was an error with the allocater.";
		case STRING_OUT_OF_BOUNDS:
			return "Attempting an operation that is out of bounds.";
		case STRING_BUFFER_TOO_SMALL:
			return "Attempting to write to a buffer that is insufficiently sized";
		default:
			return "Unknown Error.";
	}
}

/***************/
/* ALLOCATIONS */
/***************/
string_t string_init(const char *raw, size_t raw_len, string_error_codes_t *code) {
	size_t size_without_null = raw_len - 1;
	char *copied_buffer = calloc(sizeof(char), size_without_null);
	string_t result;

	if (copied_buffer == NULL) {
		if (code != NULL) 
			*code = STRING_MALLOC_ERROR;

		return result;
	}

	memcpy(copied_buffer, raw, size_without_null);

	result.capacity = size_without_null;
	result.length = size_without_null;
	result.raw = copied_buffer;

	if (code != NULL)
		*code = STRING_NONE;

	return result;
}

void string_free(string_t *str) {
	free(str->raw);
}

/**************/
/* OPERATIONS */
/**************/
string_error_codes_t string_clone(string_t *src, string_t *dest);

string_error_codes_t string_append(string_t *str, string_t *new_str) {
	size_t combined_size = str->length + new_str->length;

	if (combined_size > str->capacity) {
		size_t capacity = combined_size + (new_str->length * 2);
		char *new_buffer = realloc(str->raw, capacity);

		if (new_buffer == NULL) {
			return STRING_MALLOC_ERROR;
		}

		str->capacity = capacity;
		str->raw = new_buffer;
	}
	
	memcpy(&str->raw[str->length], new_str->raw, new_str->length);

	str->length = combined_size;

	return STRING_NONE;
}

string_error_codes_t string_append_raw(string_t *str, char *new_str, size_t new_str_len) {
	size_t size_without_null = new_str_len - 1;
	size_t combined_size = str->length + size_without_null;

	if (combined_size > str->capacity) {
		size_t capacity = combined_size + (size_without_null * 2);
		char *new_buffer = realloc(str->raw, capacity);

		if (new_buffer == NULL) {
			return STRING_MALLOC_ERROR;
		}

		str->capacity = capacity;
		str->raw = new_buffer;
	}
	
	memcpy(&str->raw[str->length], new_str, size_without_null);

	str->length = combined_size;

	return STRING_NONE;
}

string_error_codes_t string_slice(const string_t *str, size_t start, size_t end, string_t *dest) {
	if (start > end || end > str->length)
		return STRING_OUT_OF_BOUNDS;
	
	char *sliced = &str->raw[start];
	size_t sliced_length = end - start;

	string_error_codes_t initialization_result;
	string_t result = string_init(sliced, sliced_length, &initialization_result);
	*dest = result;

	return initialization_result;
}

string_error_codes_t string_pop(string_t *str, size_t idx, char* dest);
string_error_codes_t string_split_at(const string_t str, size_t idx, char* left_dest, size_t left_len, char* right_dest, size_t right_len);
string_error_codes_t string_remove_from(string_t *str, size_t idx);

string_error_codes_t string_to_c_str(const string_t *str, char *dest, size_t dest_len) {
	size_t length = str->length + 1;
	if (dest_len < length) {
		return STRING_BUFFER_TOO_SMALL;
	}
	memcpy(dest, str->raw, str->length);
	dest[str->length] = '\0'; // we don't use nulls, so we have to re-append it.

	return STRING_NONE;
}

void string_println(string_t *str) {
	if (str == NULL) {
		printf("null string_t\r\n");
	}

	char *buffer = calloc(sizeof(char), str->length + 1);
	string_to_c_str(str, buffer, str->length + 1);

	printf("String(\"%s\")\r\n", buffer);
}

char string_at(string_t *str, size_t idx, string_error_codes_t *code) {
	if (idx > str->length) {
		*code = STRING_OUT_OF_BOUNDS;
		return '\0';
	}

	return str->raw[idx];
}