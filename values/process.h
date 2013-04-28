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
  

#endif /* __PROCESS_H_ */
