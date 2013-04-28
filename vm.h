#pragma once

#if !defined(__VM_H_)
#define __VM_H_

#include "value.h"
#include "values/process.h"

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
	value_t const * nil;
	value_t **processes;
} vm_t;
  
vm_t *vm_create();
void vm_exec(vm_t *v);
int vm_attach_process(vm_t *v, value_t *proc);

#endif /* __VM_H_ */
