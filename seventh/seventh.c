#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {


	if (argc < 2) {
		printf("insufficient-arguments");
		return 0;	
	}
	for (int i = 1; i < argc; i++) {
		int strLen = strlen(argv[i]) - 1;
		char *t = &argv[i][strLen];
		char temp = *t;
		printf("%c", temp);
	}
	printf("\n");
	return 0;

}





