#include "pcc.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("error argc is invalid.\n");
		exit(1);
	}

  token = tokenize(argv[1]);
  Node *node = expr();

  generator(node);
  
	return 0;
}
