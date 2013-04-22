#pragma once

#if !defined(__VM_H_)
#define __VM_H_

#include "value.h"

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_JMP,
  OP_CALL,
  OP_RET,
  OP_NOP,
	OP_CONS,
	OP_DUMP
} opcode_t;

typedef struct {
  unsigned long opcode :5;
  long value :27;
} bytecode_t;

typedef struct {
  // Bytecode
  bytecode_t *bc;
  int bc_len;

  // Stack
  value_t **stack;

  // Registers
  int bp;
  int ip;
  int sp;

	value_t *nil;
} vm_t;
  
vm_t *vm_create();

#endif /* __VM_H_ */
