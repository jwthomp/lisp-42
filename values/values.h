#pragma once
#if !defined(__VALUES_H_)
#define __VALUES_H_

#include "../value.h"

#include "bytecode.h"

value_t const * value_create_number(int number);
value_t const * value_create_nil();
value_t const * value_create_cons(value_t const * hd, value_t const * tl);
value_t const * value_create_bytecode(bytecode_t const *bc, int bc_len);
value_t const * value_create_symbol(char const *name);
value_t const * value_create_string(char const *name);

value_t * value_create_process();

#endif /* !defined(__VALUE_H_) */
