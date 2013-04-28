#include "../value.h"

#include <stdlib.h>

value_t const * value_create_cons(value_t const * hd, value_t const * tl) {
	value_t *val = (value_t *)malloc(sizeof(value_t) + (2 * sizeof(value_t *)));
	val->type = VT_CONS;
	val->cons[0] = hd;
	val->cons[1] = tl;
	return (value_t const*) val;
}
