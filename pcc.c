#include "pcc.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("error argc is invalid.\n");
		exit(1);
	}

	current_input = argv[1];

  Token *tok = tokenize(argv[1]);
  Function *prog = parse(tok);

  generator(prog);
  
	return 0;
}
