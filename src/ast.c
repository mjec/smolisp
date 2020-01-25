#include "ast.h"

ast_node *make_list_node(ast_node *first_node) {
	n_list_t *result_value = malloc(sizeof(n_list_t));
	result_value->self = first_node;
	result_value->next = NULL;

	ast_node *result = malloc(sizeof(ast_node));
	result->type = n_list;
	result->value = result_value;
	return result;
}

ast_node *make_string_node(const char *val) {
	n_string_t *result_value = malloc(sizeof(n_string_t));
	result_value->length = strlen(val);
	result_value->value = malloc(result_value->length + 1);
	strcpy(result_value->value, val);

	ast_node *result = malloc(sizeof(ast_node));
	result->type = n_string;
	result->value = result_value;
	return result;
}

ast_node *make_int_node(n_int_t val) {
	n_int_t *result_value = malloc(sizeof(n_int_t));
	*result_value = val;

	ast_node *result = malloc(sizeof(ast_node));
	result->type = n_int;
	result->value = result_value;

	return result;
}

ast_node *make_float_node(n_float_t val) {
	n_float_t *result_value = malloc(sizeof(n_float_t));
	*result_value = val;

	ast_node *result = malloc(sizeof(ast_node));
	result->type = n_float;
	result->value = result_value;

	return result;
}

ast_node *make_function_node(ast_node *(*fn)(n_list_t *), const char *name) {
	n_function_t *result_value = malloc(sizeof(n_function_t));
	result_value->function_pointer = fn;
	result_value->name = malloc(strlen(name) + 1);
	strcpy((char *)result_value->name, name);

	ast_node *result = malloc(sizeof(ast_node));
	result->type = n_function;
	result->value = result_value;
	return result;
}

n_list_t *empty_parameter_list(void) {
	n_list_t *result = malloc(sizeof(n_list_t));
	result->self = NULL;
	result->next = NULL;

	return result;
}

void append_to_list(ast_node *node, ast_node *next) {
	if (node->type != n_list) {
		errx(EXIT_PROGRAMMER_ERROR, "BUG(%s:%d): Cannot add to a non-list node",
		     __func__, __LINE__);
	}

	n_list_t *element = (n_list_t *)node->value;
	while (element->next) {
		element = element->next;
	}
	element->next = malloc(sizeof(n_list_t));
	element->next->self = next;
}
