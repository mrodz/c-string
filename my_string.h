#pragma once
#ifndef my_string_h
#define my_string_h

#include <stdlib.h>

typedef struct string_t {
	char *raw;
	size_t length;
	size_t capacity;
} string_t;

typedef enum string_error_codes_t {
	STRING_NONE = 0,
	STRING_MALLOC_ERROR,
	STRING_OUT_OF_BOUNDS,
	STRING_BUFFER_TOO_SMALL,
} string_error_codes_t;

// inline string_t __BAD_STRING() {
// 	string_t result;
// 	return result;
// }

// #define BAD_STRING __BAD_STRING()

char *string_error_code_str(string_error_codes_t code);

/***************/
/* ALLOCATIONS */
/***************/
string_t string_init(const char *raw, size_t raw_len, string_error_codes_t *code);
void string_free(string_t *str);

/**************/
/* OPERATIONS */
/**************/
string_error_codes_t string_clone(string_t *src, string_t *dest);
string_error_codes_t string_append(string_t *str, string_t *new_str);
string_error_codes_t string_append_raw(string_t *str, char *new_str, size_t new_str_len);
string_error_codes_t string_slice(const string_t *str, size_t start, size_t end, string_t *dest);
string_error_codes_t string_pop(string_t *str, size_t idx, char* dest);
string_error_codes_t string_split_at(const string_t str, size_t idx, char* left_dest, size_t left_len, char* right_dest, size_t right_len);
string_error_codes_t string_remove_from(string_t *str, size_t idx);
string_error_codes_t string_to_c_str(const string_t *str, char *dest, size_t dest_len);

/*******************/
/* SEMI-INFALLIBLE */
/*******************/
void string_println(string_t *str);
char string_at(string_t *str, size_t idx, string_error_codes_t *code);

#endif // string_h