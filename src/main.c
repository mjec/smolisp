#include "ast.h"
#include "evaluate.h"
#include "exit.h"
#include "prelude.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	// if (argc != 2) {
	// 	errx(EXIT_NO_FILE_SPECIFIED, "Usage: %s filename.lisp", argv[0]);
	// }
	// const char *program_text = load_file(argv[1]);

	ast_node *inner = make_list_node(make_function_node(add, "add"));
	append_to_list(inner, make_int_node(42));
	append_to_list(inner, make_int_node(43));

	// ast_node *root = make_list_node(make_function_node(hello_world));
	ast_node *root = make_list_node(make_function_node(add, "add"));
	append_to_list(root, make_int_node(50));
	append_to_list(root, inner);
	append_to_list(root, make_int_node(15));
	print_node(root);
	printf(" = ");
	print_node(evaluate(root));
	printf("\n");
}
