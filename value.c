#include "value.h"

#include <stdlib.h>

value_t * value_create_number(int number) { 
	value_t * val = (value_t *)malloc(sizeof(value_t) + sizeof(int)); 
	val->type = VT_NUMBER; 
	*(int *)val->data = number; 
	return val;
}

value_t *value_create_nil() { 
	value_t *val = (value_t *)malloc(sizeof(value_t)); 
	val->type = VT_NIL; 
	return val;
}
