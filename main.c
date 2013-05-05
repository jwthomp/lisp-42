#include "vm.h"
#include "values/values.h"
#include "values/process.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
	vm_t *v = vm_create(); 
	value_t const *nil = value_create_nil();

	value_t *proc = value_create_process();

	value_t const *val = process_create_symbol(proc, "val");
	value_t const *val2 = process_create_symbol(proc, "val");

	printf("val: %p =? val2: %p\n", val, val2);

	bytecode_t bt[] = { 
	// Those are symbols
	// Binding assigns them to something
		{OP_PUSH, val},
		{OP_PUSH, value_create_number(1)},
		{OP_BIND, nil}, 
		{OP_PUSH, val2},
		{OP_PUSH, value_create_number(2)},
		{OP_BIND, nil}, 
		{OP_PUSH, val},
		{OP_LOAD, nil},
		{OP_PUSH, val2},
		{OP_LOAD, nil},
		{OP_DUMP, nil},
		{OP_RET, nil} 
	}; 


	int bc_len = 17;
	value_t const *bc = value_create_bytecode(bt, bc_len);
	printf("bc: %p len: %d\n", bc, bc_len);

	process_attach_bytecode(proc, bc);
	printf("proc: %p\n", proc);
	process_print_symbols(proc);


	vm_attach_process(v, proc);

	vm_exec(v);

	process_print_symbols(proc);

	// debug_print_stack(&v); 
	return 0;
}
