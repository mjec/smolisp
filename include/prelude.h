#ifndef PRELUDE_H
#define PRELUDE_H

#include "ast.h"

ast_node *hello_world(n_list_t *args);
ast_node *add(n_list_t *args);
ast_node *add_int(n_list_t *args);
ast_node *add_float(n_list_t *args);

#endif
