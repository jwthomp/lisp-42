#include "../value.h"
#include "values.h"

static value_t const *int_null = (value_t *)0;
static value_t const *int_nil = (value_t *)0;

value_t const * value_create_nil() { 
	if (int_nil == int_null) {
		value_t const * val = value_create_cons(int_null, int_null);
		int_nil = val;
		return val;
	} else {
		return int_nil;
	}
}

