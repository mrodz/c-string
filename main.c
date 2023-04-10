#include "my_string.h"

#include <stdio.h>

int main(int argc, const char *argv[]) {
	char name[] = "Mateo";
	string_t my_string = string_init(name, sizeof(name), NULL);

	char name2[] = "Dylan";
	string_t dylan = string_init(name2, sizeof(name2), NULL);

	string_error_codes_t code;

	if (code = string_append(&my_string, &dylan)) 
		printf("Error: %s\r\n", string_error_code_str(code));

	char as_bytes[100];

	string_println(&my_string);

	if (code = string_append_raw(&my_string, ", Hello World", 14)) 
		printf("Error: %s\r\n", string_error_code_str(code));

	string_println(&my_string);

	string_t hello;

	if (code = string_slice(&my_string, 13, 17, &hello)) 
		printf("Error: %s\r\n", string_error_code_str(code));

	string_println(&hello);
}
