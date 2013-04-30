#include "process.h"

#include "../value.h"
#include "values.h"
#include "../vm.h"

#include <stdio.h>
#include <stdlib.h>



value_t *value_create_process(value_t const * bytecode) {
	value_t *proc = (value_t *)malloc(sizeof(value_t) + sizeof(process_t));
	proc->type = VT_PROCESS;
	process_t *data = (process_t *)proc->data;
	data->bp = -1;
	data->sp = 0;
	data->ip = 0;
	data->stack = (value_t const **) malloc(sizeof(value_t *) * 64);
	data->symbols = (value_t const *) 0;
	data->bc = bytecode;

	return proc;
}


value_t const *process_add_symbol(value_t *process, value_t const* symbol) {
	process_t *proc_data = (process_t *)process->data;
	value_t const *nil = value_create_nil();

	if (proc_data->symbols == nil) {
		proc_data->symbols = value_create_cons(symbol, nil);
	} else {
		proc_data->symbols = value_create_cons(symbol, proc_data->symbols);
	}

	return symbol;
}

value_t const *process_create_symbol(value_t *process, char const *name) {
	value_t const *symbol = value_create_symbol(name);
	process_add_symbol(process, symbol);
	return symbol;
}

void process_print_symbols(value_t *process) {
	process_t *proc_data = (process_t *)process->data;
	debug_print_value(proc_data->symbols);
}

