#pragma once
#if !defined(__VALUE_H_)
#define __VALUE_H_

typedef enum { 
	VT_NUMBER, 
	VT_SYMBOL, 
	VT_CONS, 
} value_type_t;

typedef struct value_s {
	value_type_t type; 
	union { 
		char data[0]; 
		// VT_CONS(2)-> [0] car, [1] cdr 
		// VT_SYMBOL(4)-> [0] name, [1] next symbol in symbol table, [2] lexical bind, [3] dynamic bind
		struct value_s const *cons[0]; 
	};
} value_t;

value_t const * value_create_number(int number);
value_t const * value_create_nil();
value_t const * value_create_cons(value_t const * hd, value_t const * tl);

#endif /* !defined(__VALUE_H_) */
