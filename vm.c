#include "vm.h"

#include "value.h"

#include <stdio.h>
#include <stdlib.h>

void debug_print_value(value_t const* nil, value_t const *val);


value_t const ** stack_alloc() {
  return (value_t const **) malloc(sizeof(value_t *) * 64);
}

vm_t *vm_create() {
	vm_t *vm = (vm_t *)malloc(sizeof(vm_t));
  vm->stack = stack_alloc();
  vm->ip = 0;
  vm->sp = 0;
  vm->bp = -1;
	vm->nil = value_create_nil();

	return vm;
}


void debug_print_elts(value_t const* nil, value_t const *val) {
	if(val == nil) {
		return;
	}

	// Print head of cons
	debug_print_value(nil, val->cons[0]);

	if(val->cons[1] == nil) {
		return;
	} 

	printf(" ");
	
	if(val->cons[1]->type != VT_CONS) {
		printf(". ");
		debug_print_value(nil, val->cons[1]);
		return;
	} 

	debug_print_elts(nil, val->cons[1]);
}

void debug_print_value(value_t const* nil, value_t const *val) {

  switch(val->type) {
    case VT_NUMBER:
      printf("%d", *(int *)val->data);
			break;
		case VT_CONS:
			printf("(");
			debug_print_elts(nil, val);
			printf(")");
			break;
  }
}

void debug_print_bytecode(value_t const* nil, bytecode_t *code) {
	switch(code->opcode) {
		case OP_PUSH: printf("OP_PUSH: "); break;
		case OP_POP: printf("OP_POP: "); break;
  	case OP_JMP: printf("OP_JMP: "); break;
  	case OP_CALL: printf("OP_CALL: "); break;
  	case OP_RET: printf("OP_RET: "); break;
  	case OP_NOP: printf("OP_NOP: "); break;
  	case OP_CONS: printf("OP_CONS: "); break;
  	case OP_CAR: printf("OP_CAR: "); break;
  	case OP_CDR: printf("OP_CDR: "); break;
  	case OP_DUMP: printf("OP_DUMP: "); break;
		case OP_EQ: printf("OP_EQ: "); break;
		case OP_DUP: printf("OP_DUP: "); break;
		default: printf("UNKNOWN OPCODE: "); break;
	}
	debug_print_value(nil, code->value);
	printf("\n");
}

void debug_print_stack(vm_t *v) {
  printf("sp: %d\n", v->sp);
	int sp = v->sp;
  while(sp--) {
		printf("%d] ", sp); 
    debug_print_value(v->nil, v->stack[sp]);
		printf("\n");
  }
}

void vm_exec(vm_t *v) {
	value_t const *cdr;
	value_t const *car; 
	value_t const *cons; 
	value_t const *val1;
	value_t const *val2;

  while(1) {
    bytecode_t *bc = &v->bc[v->ip++];

    printf("ip: %d ] ", v->ip);
		debug_print_bytecode(v->nil, bc);

		

    switch(bc->opcode) {
      case OP_PUSH:
        v->stack[v->sp++] = bc->value;
        break;
      case OP_POP:
        v->sp--;
        break;
      case OP_JMP:
        break;
      case OP_CALL:
        break;
      case OP_RET:
        if (v->bp == -1) {
          return;
        }
        break;
			case OP_DUMP:
				debug_print_stack(v);
				break;

			case OP_CONS:
				v->sp--;
				cdr = v->stack[v->sp];
				v->sp--;
				car = v->stack[v->sp];
				v->stack[v->sp++] = value_create_cons(car, cdr);
				break;

			case OP_CAR:
				v->sp--;
				cons = v->stack[v->sp];
				v->stack[v->sp++] = cons->cons[0];
				break;


			case OP_CDR:
				v->sp--;
				cons = v->stack[v->sp];
				v->stack[v->sp++] = cons->cons[1];
				break;

			case OP_DUP:
				val1 = v->stack[v->sp - 1];
				v->stack[v->sp++] = val1;				
				break;

			case OP_EQ:
				val1 = v->stack[v->sp - 1];
				val2 = v->stack[v->sp - 2];
				v->sp -= 2;
				v->stack[v->sp++] = val1 == val2 ? value_create_number(1) : value_create_number(0);
				break;
			
				
      case OP_NOP:
        break;
    }
  }
}

