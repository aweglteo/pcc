#include "pcc.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("error argc is invalid.\n");
		exit(1);
	}

	current_input = argv[1];

  Token *tok = tokenize(argv[1]);
  Node *node = parse(tok);

  generator(node);
  
	return 0;
}
