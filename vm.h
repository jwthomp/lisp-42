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
	OP_CAR,
	OP_CDR,
	OP_DUP,
	OP_EQ,
	OP_DUMP
} opcode_t;



typedef struct {
  unsigned long opcode;
	value_t const * value;
} bytecode_t;

typedef struct {
  // Bytecode
  bytecode_t *bc;
  int bc_len;

  // Stack
  value_t const ** stack;

  // Registers
  int bp;
  int ip;
  int sp;

	value_t const * nil;
} vm_t;
  
vm_t *vm_create();
void vm_exec(vm_t *v);

#endif /* __VM_H_ */
