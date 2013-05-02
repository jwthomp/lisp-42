#pragma once

#if !defined(__PROCESS_H_)
#define __PROCESS_H_

#include "../value.h"
#include "bytecode.h"


typedef struct {
  // Bytecode
	value_t const *bc;

  // Stack
  value_t const **stack;

  // Registers
  int bp;
  int ip;
  int sp;

	// Cons list of symbols
	value_t const *symbols;
} process_t;
  

value_t *process_attach_bytecode(value_t *process, value_t const *bytecode);
value_t const *process_add_symbol(value_t *process, value_t const* symbol);
value_t const *process_create_symbol(value_t *process, char const *name);

void process_print_symbols(value_t *process);

#endif /* __PROCESS_H_ */
