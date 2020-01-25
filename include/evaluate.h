#ifndef EVALUATE_H
#define EVALUATE_H

#include "ast.h"

ast_node *call_function(n_function_t *fn, n_list_t *parameters);
ast_node *evaluate(ast_node *node);
void print_node(ast_node *node);
void print_list(n_list_t *list_node);

#endif
