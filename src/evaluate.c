#include "evaluate.h"
#include "exit.h"
#include <stdio.h>

ast_node *call_function(n_function_t *fn, n_list_t *parameters) {
	return fn->function_pointer(parameters);
}

ast_node *evaluate(ast_node *node) {
	switch (node->type) {
	case n_function:
		return call_function((n_function_t *)node->value,
		                     empty_parameter_list());
	case n_list:
		if (((n_list_t *)node->value)->self == NULL) {
			return node;
		}
		if (((n_list_t *)node->value)->self->type != n_function) {
			return node;
		}
		n_list_t *list = (n_list_t *)node->value;
		n_function_t *fn = list->self->value;
		if (list->next == NULL) {
			return call_function(fn, empty_parameter_list());
		}
		n_list_t *parameter_list = empty_parameter_list();
		n_list_t *current_element = parameter_list;

		while (list->next && list->next->self) {
			list = list->next;
			ast_node *evaluated = evaluate(list->self);
			n_list_t *next_element = malloc(sizeof(n_list_t));
			next_element->self = evaluated;
			next_element->next = NULL;
			if (current_element->self == NULL) {
				current_element->self = next_element->self;
				free(next_element);
			} else {
				current_element->next = next_element;
				current_element = next_element;
			}
		}
		return call_function(fn, parameter_list);
		break;
	case n_string:
	case n_int:
	case n_float:
		return node;
	default:
		errx(EXIT_PROGRAMMER_ERROR, "BUG (%s:%d): Unknown node type %d",
		     __func__, __LINE__, node->type);
	}
}

void print_list(n_list_t *list_node) {
	printf("(");
	while (list_node->self) {
		print_node(list_node->self);
		list_node = list_node->next;
		if (!list_node) {
			break;
		}
		printf(" ");
	}
	printf(")");
}

void print_node(ast_node *node) {
	switch (node->type) {
	case n_function:
		printf("%s", ((n_function_t *)node->value)->name);
		break;
	case n_list:
		print_list((n_list_t *)node->value);
		break;
	case n_string:
		for (size_t i = 0; i < ((n_string_t *)node->value)->length; i++) {
			printf("%c", ((n_string_t *)node->value)->value[i]);
		}
		break;
	case n_int:
		printf("%ld", *(n_int_t *)node->value);
		break;
	case n_float:
		printf("%f", *(n_float_t *)node->value);
		break;
	default:
		printf("Unknown node!");
		break;
	}
}
