#include "vm.h"

int main(int argc, char *argv[]) {
	vm_t *v = vm_create(); 
	bytecode_t bt[] = { 
		{OP_PUSH, 1}, 
		{OP_PUSH, 2}, 
		{OP_PUSH, 4}, 
		{OP_PUSH, 8}, 
		{OP_DUMP, 0}, 
		{OP_CALL, 0}, 
		{OP_POP, 0}, 
		{OP_RET, 0} 
	}; 

	v->bc = bt; 
	vm_exec(v);

	// debug_print_stack(&v); 
	return 0;
}
