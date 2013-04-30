#pragma once

#if !defined(PROCESS_H_)
#define PROCESS_H_

#include "value.h"

value_t const *process_add_symbol(value_t *process, value_t const* symbol);
value_t const *process_create_symbol(value_t *process, char const *name);

#endif // !defined(PROCESS_H_)
