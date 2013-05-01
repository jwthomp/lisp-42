#include "../value.h"
#include "values.h"

#include <string.h>
#include <stdlib.h>

value_t const * value_create_symbol(char const *name) { 
	value_t const * str = value_create_string(name);
	value_t const * nil = value_create_nil();

	value_t * val = (value_t *)malloc(sizeof(value_t) + (sizeof(value_t *) * 3));
	val->type = VT_SYMBOL; 
	val->cons[0] = str;
	val->cons[1] = nil;
	val->cons[2] = nil;

	return (value_t const *)val;
}

