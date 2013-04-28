#include "process.h"

#include "../value.h"

#include <stdio.h>
#include <stdlib.h>


value_t const ** stack_alloc() {
  return (value_t const **) malloc(sizeof(value_t *) * 64);
}


value_t *value_create_process(value_t const * bytecode) {
	value_t *proc = (value_t *)malloc(sizeof(value_t) + sizeof(process_t));
	proc->type = VT_PROCESS;
	process_t *data = (process_t *)proc->data;
	data->bp = -1;
	data->sp = 0;
	data->ip = 0;
	data->stack = stack_alloc();
	data->symbols = (value_t const *) 0;
	data->bc = bytecode;

	return proc;
}



