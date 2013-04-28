#include "bytecode.h"

#include <stdlib.h>
#include <string.h>

value_t const * value_create_bytecode(bytecode_t const *bc, int bc_len) {
	int bc_size = sizeof(bytecode_t) * bc_len;
  value_t *bcv = (value_t *)malloc(sizeof(value_t) + bc_size);
  bcv->type = VT_BYTECODE;
	memcpy((void *)bcv->data, bc, bc_size);
	return bcv;
}

