#include "../value.h"

#include <string.h>
#include <stdlib.h>

value_t const * value_create_string(char const *name) { 
	int name_size = strlen(name) + 1;
	value_t * val = (value_t *)malloc(sizeof(value_t) + name_size);
	val->type = VT_STRING; 
	memcpy((void *)val->data, name, name_size);


	return (value_t const *)val;
}

