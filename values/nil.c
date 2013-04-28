#include "../value.h"
#include "values.h"

static value_t const *nil = (value_t *)0;

value_t const * value_create_nil() { 
	value_t const * val = value_create_cons(nil, nil);
	return val;
}

