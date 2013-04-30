#include "vm.h"
#include "values/values.h"
#include "values/process.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	vm_t *v = vm_create(); 
	value_t const *nil = value_create_nil();


	bytecode_t bt[] = { 
	// Those are symbols
	// Binding assigns them to something
		{OP_PUSH, nil},
		{OP_PUSH, nil},
		{OP_CONS, nil},
		{OP_DUMP, nil},
		{OP_RET, nil} 
	}; 


	int bc_len = 17;
	value_t const *bc = value_create_bytecode(bt, bc_len);
	printf("bc: %p len: %d\n", bc, bc_len);

	value_t *proc = value_create_process(bc);
	printf("proc: %p\n", proc);

	process_create_symbol(proc, "nil");
	process_create_symbol(proc, "+");
	process_create_symbol(proc, "-");


	vm_attach_process(v, proc);

	vm_exec(v);

	process_print_symbols(proc);

	// debug_print_stack(&v); 
	return 0;
}
