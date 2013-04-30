#include "../value.h"
#include "values.h"

#include <string.h>
#include <stdlib.h>

value_t const * value_create_symbol(char const *name) { 
	int name_len = strlen(name) + 1;
	value_t * val = (value_t *)malloc(sizeof(value_t) + name_len);
	val->type = VT_SYMBOL; 
	memcpy((void *)val->data, name, name_len);

	return (value_t const *)val;
}

