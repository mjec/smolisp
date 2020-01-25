#include "prelude.h"
#include "exit.h"

ast_node *hello_world(n_list_t *args) {
	if (args->self || args->next) {
		errx(EXIT_SYNTAX_ERROR,
		     "hello_world called with arguments (should have none)");
	}
	return make_string_node("Hello, world\n");
}

ast_node *add(n_list_t *args) {
	if (!args) {
		errx(EXIT_PROGRAMMER_ERROR, "BUG(%s:%d): Called with NULL args",
		     __func__, __LINE__);
	}
	if (!args->self) {
		errx(EXIT_SYNTAX_ERROR, "add called with no arguments");
	}
	switch (args->self->type) {
	case n_int:
		return add_int(args);
	case n_float:
		return add_float(args);
	default:
		errx(EXIT_SYNTAX_ERROR,
		     "add called with non-integer, non-float first argument");
	}
}

ast_node *add_int(n_list_t *args) {
	n_int_t sum = 0;
	n_list_t *current_element = args;
	while (current_element && current_element->self) {
		if (current_element->self->type != n_int) {
			errx(EXIT_SYNTAX_ERROR, "add called with mixed arguments");
		}
		n_int_t *value = (n_int_t *)current_element->self->value;
		sum += *value;
		current_element = current_element->next;
	}
	ast_node *result = malloc(sizeof(ast_node));
	n_int_t *result_value = malloc(sizeof(n_int_t));
	*result_value = sum;
	result->type = n_int;
	result->value = result_value;
	return result;
}

ast_node *add_float(n_list_t *args) {
	n_float_t sum = 0;
	n_list_t *current_element = args;
	while (current_element && current_element->self) {
		if (current_element->self->type != n_float) {
			errx(EXIT_SYNTAX_ERROR, "add called with mixed arguments");
		}
		n_float_t *value = (n_float_t *)current_element->self->value;
		sum += *value;
		current_element = current_element->next;
	}
	ast_node *result = malloc(sizeof(ast_node));
	n_float_t *result_value = malloc(sizeof(n_float_t));
	*result_value = sum;
	result->type = n_float;
	result->value = result_value;
	return result;
}
