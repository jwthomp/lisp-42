#include "vm.h"

#include <stdio.h>
#include <stdlib.h>

value_t * value_create_number(int number) {
  value_t * val = (value_t *)malloc(sizeof(value_t) + sizeof(int));
  val->type = VT_NUMBER;
  *(int *)val->data = number;
  return val;
}

debug_print_value(value_t *val) {
  switch(val->type) {
    case VT_NUMBER:
      printf("number: %d\n", *(int *)val->data);
  }
}

debug_print_stack(vm_t *v) {
  printf("sp: %d\n", v->sp);
  while(v->sp--) {
    debug_print_value(v->stack[v->sp]);
  }
}

void vm_exec(vm_t *v) {
  while(1) {
    bytecode_t *bc = &v->bc[v->ip++];

    printf("ip: %d ] ", v->ip);

    switch(bc->opcode) {
      case OP_PUSH:
        printf("OP_PUSH: %d\n", bc->value);
        v->stack[v->sp++] = value_create_number(bc->value);
        break;
      case OP_POP:
        printf("OP_POP: %d\n", bc->value);
        v->sp--;
        break;
      case OP_JMP:
        printf("OP_JMP: %d\n", bc->value);
        break;
      case OP_CALL:
        printf("OP_CALL: %d\n", bc->value);
        break;
      case OP_RET:
        printf("OP_RET: %d\n", bc->value);
        if (v->bp == -1) {
          return;
        }
        break;
      case OP_NOP:
        printf("OP_NOP: %d\n", bc->value);
        break;
    }
  }
}

value_t ** stack_alloc() {
  return (value_t **) malloc(sizeof(value_t *) * 64);
}

int main(int argc, char *argv[]) {
  vm_t v;

  v.bc = (bytecode_t *)malloc(sizeof(bytecode_t) * 4);
  v.bc[0].opcode = OP_PUSH;
  v.bc[0].value = 1;
  v.bc[1].opcode = OP_CALL;
  v.bc[1].value = 0;
  v.bc[2].opcode = OP_POP;
  v.bc[2].value = 0;
  v.bc[3].opcode = OP_RET;
  v.bc[3].value = 0;
  v.ip = 0;
  v.sp = 0;
  v.bp = -1;

  v.stack = stack_alloc();

  vm_exec(&v);

  debug_print_stack(&v);

  return 0;
}
