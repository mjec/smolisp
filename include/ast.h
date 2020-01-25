#ifndef AST_H
#define AST_H

#include "exit.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ast_node ast_node;
typedef enum node_type {
	n_list,
	n_string,
	n_int,
	n_float,
	n_symbol,
	n_function,
} node_type;
typedef struct n_list_t n_list_t;
typedef struct n_string_t n_string_t;
typedef int64_t n_int_t;
typedef double n_float_t;
typedef struct n_symbol_t n_symbol_t;
typedef struct n_function_t n_function_t;

struct n_list_t {
	ast_node *self;
	n_list_t *next;
};

struct n_string_t {
	char *value;
	size_t length;
};

struct n_symbol_t {
	const char *name;
};

struct n_function_t {
	const char *name;
	ast_node *(*function_pointer)(n_list_t *);
};

struct ast_node {
	node_type type;
	void *value;
};

ast_node *make_list_node(ast_node *first_node);
ast_node *make_string_node(const char *val);
ast_node *make_int_node(n_int_t val);
ast_node *make_float_node(n_float_t val);
ast_node *make_function_node(ast_node *(*fn)(n_list_t *), const char *name);

n_list_t *empty_parameter_list(void);
void append_to_list(ast_node *node, ast_node *next);

#endif
