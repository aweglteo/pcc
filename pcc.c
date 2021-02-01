#include<stdio.h>
#include<stdlib.h>

// Intel記法
int main(int argc, char **argv) {
	if (argc != 2) {
		printf("error argc is invalid!\n");
		exit(1);
	}

	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");
	printf("	mov rax, %d\n", atoi(argv[1]));
	printf("	ret\n");
	return 0;
}

