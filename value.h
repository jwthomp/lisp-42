#pragma once
#if !defined(__VALUE_H_)
#define __VALUE_H_

typedef enum { 
	VT_NUMBER, 
	VT_SYMBOL, 
	VT_CONS, 
	VT_NIL
} value_type_t;

typedef struct value_s {
	value_type_t type; 
	union { 
		char data[0]; 
		struct value_s *cons[0]; 
	};
} value_t;

value_t * value_create_number(int number);
value_t *value_create_nil();
value_t *value_create_cons(value_t *hd, value_t *tl);

#endif /* !defined(__VALUE_H_) */
