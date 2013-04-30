#include "process.h"
#include "values/values.h"

value_t const *process_add_symbol(value_t *process, value_t const* symbol) {
	return symbol;
}

value_t const *process_create_symbol(value_t *process, char const *name) {
	value_t const *symbol = value_create_symbol(name);
	process_add_symbol(process, symbol);
	return symbol;
}
