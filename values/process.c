#include "process.h"

#include "../value.h"
#include "values.h"
#include "../vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



value_t *value_create_process(value_t const * bytecode) {
	value_t *proc = (value_t *)malloc(sizeof(value_t) + sizeof(process_t));
	proc->type = VT_PROCESS;

	process_t *data = (process_t *)proc->data;
	data->bp = -1;
	data->sp = 0;
	data->ip = 0;
	data->stack = (value_t const **) malloc(sizeof(value_t *) * 64);
	data->symbols = value_create_nil();
	data->bc = value_create_nil();

	return proc;
}

value_t *process_attach_bytecode(value_t * proc, value_t const * bytecode) {
	process_t *data = (process_t *)proc->data;
	data->bc = bytecode;
	return proc;
}


value_t const *process_add_symbol(value_t *process, value_t const* symbol) {
	process_t *proc_data = (process_t *)process->data;

	proc_data->symbols = value_create_cons(symbol, proc_data->symbols);

	return symbol;
}

value_t const *process_create_symbol(value_t *process, char const *name) {
	// First check if this symbol already exists..
	process_t *proc_data = (process_t *)process->data;
	value_t const *nil = value_create_nil();
	value_t const *cons = proc_data->symbols;
	value_t const *symbol = nil;

	while(cons != nil) {
		if (!strcmp(name, cons->cons[0]->cons[0]->data)) {
			symbol = cons->cons[0];
			break;
		}

		cons = cons->cons[1];
	}

	if (symbol == nil) {
		symbol = value_create_symbol(name);
		process_add_symbol(process, symbol);
	}
	

	// Otherwise create a new one
	return symbol;
}

void process_print_symbols(value_t *process) {
	process_t *proc_data = (process_t *)process->data;

	printf("Symbols For Proc: %p\n", process);
	printf("-------------------\n");

	value_t const *nil = value_create_nil();
	value_t const *cons = proc_data->symbols;
	while (cons != nil) {
		value_t const *sym = cons->cons[0];
		debug_print_value(sym->cons[0]);
		printf("\n Dynamic Bindings \n");
		debug_print_value(sym->cons[1]);
		printf("\n");
		cons = cons->cons[1];
	}
	
	printf("-------------------\n");
}

