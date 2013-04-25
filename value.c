#include "value.h"

#include <stdlib.h>

static value_t const *nil = (value_t *)0;

value_t const * value_create_number(int number) { 
	value_t * val = (value_t *)malloc(sizeof(value_t) + sizeof(int)); 
	val->type = VT_NUMBER; 
	*(int *)val->data = number; 
	return (value_t const *)val;
}

value_t const * value_create_nil() { 
	value_t const * val = value_create_cons(nil, nil);
	return val;
}

value_t const * value_create_cons(value_t const * hd, value_t const * tl) {
	value_t *val = (value_t *)malloc(sizeof(value_t) + (2 * sizeof(value_t *)));
	val->type = VT_CONS;
	val->cons[0] = hd;
	val->cons[1] = tl;
	return (value_t const*) val;
}
