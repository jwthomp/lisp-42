#pragma once

#ifndef __VM_H_
#define __VM_H_

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_JMP,
  OP_CALL,
  OP_RET,
  OP_NOP
} opcode_t;

typedef struct {
  unsigned long opcode :5;
  long value :27;
} bytecode_t;

typedef enum {
  VT_NUMBER,
  VT_SYMBOL,
  VT_CONS
} value_type_t;

typedef struct value_s {
  value_type_t type;
  union {
    char data[0];
    struct value_s *cons[0];
  };
} value_t;

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
} vm_t;
  

#endif /* __VM_H_ */
