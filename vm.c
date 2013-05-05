#include "vm.h"

#include "value.h"
#include "values/values.h"
#include "values/process.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 64

void debug_print_value(value_t const *val);

static value_t const *nil = (value_t const *)0;

vm_t *vm_create() {
	// JWT: This should get moved to a vlisp init at some point
	if (nil == 0) {
		nil = value_create_nil();
	}

	vm_t *vm = (vm_t *)malloc(sizeof(vm_t));
	vm->processes = (value_t **)malloc(sizeof(value_t *) * MAX_PROCESSES);
	for (int i = 0; i < MAX_PROCESSES; i++) {
		vm->processes[i] = (value_t *)nil;
	}

	return vm;
}

int vm_attach_process(vm_t *vm, value_t *proc) {
	for (int i = 0; i < MAX_PROCESSES; i++) {
		if (vm->processes[i] == nil) {
			vm->processes[i] = proc;
			return i;
		}
	}

	return -1;
}


void debug_print_elts(value_t const *val) {
	if(val == nil) {
		return;
	}

	// Print head of cons
	debug_print_value(val->cons[0]);

	if(val->cons[1] == nil) {
		return;
	} 

	printf(" ");
	
	if(val->cons[1]->type != VT_CONS) {
		printf(". ");
		debug_print_value(val->cons[1]);
		return;
	} 

	debug_print_elts(val->cons[1]);
}

void debug_print_value(value_t const *val) {

  switch(val->type) {
    case VT_NUMBER:
      printf("%d", *(int *)val->data);
			break;
		case VT_CONS:
			printf("(");
			debug_print_elts(val);
			printf(")");
			break;
		case VT_STRING:
			printf("\"%s\"", (char const *)val->data);
			break;
		case VT_SYMBOL:
			printf("%s", (char const *)val->cons[0]->data);
			break;
		default:
			printf("unknown");
			break;
  }
}

void debug_print_bytecode(bytecode_t *code) {
	switch(code->opcode) {
		case OP_PUSH: printf("OP_PUSH: "); break;
		case OP_POP: printf("OP_POP: "); break;
		case OP_LOAD: printf("OP_LOAD: "); break;
  	case OP_JMP: printf("OP_JMP: "); break;
  	case OP_CALL: printf("OP_CALL: "); break;
  	case OP_RET: printf("OP_RET: "); break;
  	case OP_NOP: printf("OP_NOP: "); break;
  	case OP_CONS: printf("OP_CONS: "); break;
  	case OP_CAR: printf("OP_CAR: "); break;
  	case OP_CDR: printf("OP_CDR: "); break;
  	case OP_DUMP: printf("OP_DUMP: "); break;
		case OP_EQ: printf("OP_EQ: "); break;
		case OP_BIND: printf("OP_BIND: "); break;
		case OP_DUP: printf("OP_DUP: "); break;
		case OP_ISNULL: printf("OP_ISNULL: "); break;
		case OP_ISATOM: printf("OP_ISATOM: "); break;
		default: printf("UNKNOWN OPCODE: "); break;
	}
	debug_print_value(code->value);
	printf("\n");
}

void debug_print_stack(process_t *proc) {
  printf("sp: %d\n", proc->sp);
	int sp = proc->sp;
  while(sp--) {
		printf("%d] ", sp); 
    debug_print_value(proc->stack[sp]);
		printf("\n");
  }
}

value_t *get_cur_proc(vm_t *vm) {
	return vm->processes[0];
}

void vm_exec(vm_t *vm) {
	value_t const *cdr;
	value_t const *car; 
	value_t const *cons; 
	value_t const *val1;
	value_t const *val2;

  while(1) {
		value_t *cur_proc = get_cur_proc(vm);
		process_t *proc = (process_t *)cur_proc->data;

    bytecode_t const *bcp = (bytecode_t const *)proc->bc->data;
		bytecode_t bc = bcp[proc->ip++];

    printf("ip: %d ] ", proc->ip);
		debug_print_bytecode(&bc);

		value_t const **stack = proc->stack;

    switch(bc.opcode) {
      case OP_PUSH:
        stack[proc->sp++] = bc.value;
        break;
      case OP_POP:
        proc->sp--;
        break;
      case OP_JMP:
        break;
      case OP_CALL:
        break;
      case OP_RET:
        if (proc->bp == -1) {
          return;
        }
        break;
			case OP_DUMP:
				debug_print_stack(proc);
				break;

			case OP_CONS:
				proc->sp--;
				cdr = stack[proc->sp];
				proc->sp--;
				car = stack[proc->sp];
				stack[proc->sp++] = value_create_cons(car, cdr);
				break;

			case OP_CAR:
				proc->sp--;
				cons = stack[proc->sp];
				stack[proc->sp++] = cons->cons[0];
				break;


			case OP_CDR:
				proc->sp--;
				cons = stack[proc->sp];
				stack[proc->sp++] = cons->cons[1];
				break;

			case OP_BIND:
				val1 = stack[proc->sp - 1];
				val2 = stack[proc->sp - 2];
				proc->sp -= 2;

				// Currently only supporting dynamic binding
				{
					value_t *sym = (value_t *)val2;
					sym->cons[1] = value_create_cons(val1, sym->cons[1]);
				}

				break;

			case OP_LOAD:
				// Dynamic value is stored at the head of the cons[1] list
				stack[proc->sp - 1] = stack[proc->sp - 1]->cons[1]->cons[0];
				break;
				

			case OP_DUP:
				val1 = stack[proc->sp - 1];
				stack[proc->sp++] = val1;				
				break;

			case OP_EQ:
				val1 = stack[proc->sp - 1];
				val2 = stack[proc->sp - 2];
				proc->sp -= 2;
				stack[proc->sp++] = val1 == val2 ? value_create_number(1) : value_create_number(0);
				break;

			case OP_ISNULL:
				val1 = stack[proc->sp - 1];
				if (val1 == nil) {
					stack[proc->sp - 1] = process_create_symbol(cur_proc, "#t");
				} else {
					stack[proc->sp - 1] = nil;
				}
				break;

			case OP_ISATOM:
				if (stack[proc->sp - 1]->type == VT_CONS) {
					stack[proc->sp - 1] = nil;
				} else {
					stack[proc->sp - 1] = process_create_symbol(cur_proc, "#t");
				}
				break;
				
      case OP_NOP:
        break;
    }
  }
}

