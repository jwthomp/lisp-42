#include "vm.h"
#include "values/values.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	vm_t *v = vm_create(); 
	bytecode_t bt[] = { 
		{OP_PUSH, value_create_number(1)},
		{OP_PUSH, value_create_symbol("foo")},
		{OP_BIND, v->nil},
		{OP_RET, v->nil} 
	}; 

	int bc_len = 17;
	value_t const *bc = value_create_bytecode(bt, bc_len);
	printf("bc: %p len: %d\n", bc, bc_len);

	value_t *proc = value_create_process(bc);
	printf("proc: %p\n", proc);

	vm_attach_process(v, proc);

	vm_exec(v);

	// debug_print_stack(&v); 
	return 0;
}
