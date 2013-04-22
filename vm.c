#include "vm.h"

#include "value.h"

#include <stdio.h>
#include <stdlib.h>

value_t ** stack_alloc() {
  return (value_t **) malloc(sizeof(value_t *) * 64);
}

vm_t *vm_create() {
	vm_t *vm = (vm_t *)malloc(sizeof(vm_t));
  vm->stack = stack_alloc();
  vm->ip = 0;
  vm->sp = 0;
  vm->bp = -1;

	return vm;
}

debug_print_value(value_t *val) {
  switch(val->type) {
    case VT_NUMBER:
      printf("number: %d\n", *(int *)val->data);
  }
}

debug_print_stack(vm_t *v) {
  printf("sp: %d\n", v->sp);
	int sp = v->sp;
  while(sp--) {
		printf("%d] ", sp); 
    debug_print_value(v->stack[sp]);
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
			case OP_DUMP:
				debug_print_stack(v);
				break;
				
      case OP_NOP:
        printf("OP_NOP: %d\n", bc->value);
        break;
    }
  }
}

