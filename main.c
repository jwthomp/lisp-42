#include "vm.h"

int main(int argc, char *argv[]) {
	vm_t *v = vm_create(); 
	bytecode_t bt[] = { 
		{OP_PUSH, value_create_number(1)},
		{OP_PUSH, v->nil},
		{OP_CONS, v->nil},
		{OP_PUSH, value_create_number(2)},
		{OP_PUSH, value_create_number(3)},
		{OP_PUSH, value_create_number(4)},
		{OP_CONS, v->nil},
		{OP_CONS, v->nil},
		{OP_CONS, v->nil},
		{OP_DUP, v->nil},
		{OP_CDR, v->nil},
		{OP_DUMP, v->nil},
		{OP_RET, v->nil} 
	}; 

	v->bc = bt; 
	vm_exec(v);

	// debug_print_stack(&v); 
	return 0;
}
