#pragma once

#if !defined(__BYTECODE_H_)
#define __BYTECODE_H_

#include "../value.h"


typedef struct {
  unsigned long opcode;
	value_t const * value;
} bytecode_t;


#endif /* __BYTECODE_H_ */
