#include <stdio.h>
#include <stdlib.h>

int isPrime(int num);

int main(int argc, char **argv) {	
	if (argc != 2) {
		printf("Please enter a file name or just enter two arguments\n");
		exit(0);	
	}	
	char *filename = argv[1];	
	FILE *fp;
	fp = fopen(filename,"r");
	if (fp == NULL) {
		printf("Invalid file name\n");
		exit(0);
	}
	
	
	int a1;
	int count;
	if (fscanf(fp,"%d", &count) == EOF) {
		printf("File is empty\n");
		exit(0);
	}
	int i;
	for (i = 1; i <= count; i++) {	
		fscanf(fp,"%d",&a1);
		int *a1p = &a1;\
		while (*a1p != 0) {
			if (isPrime(*a1p) == 1) {
				*a1p = a1 / 10;	
			} else {
				break;
			}
		}
		if (a1 == 0) {
			printf("yes\n");		
		} else {
			printf("no\n");		
		}
	}

	return 0;
	
}

int isPrime(int num) {
	int j;
	for (j = 2; j < num; j++) {
		if (num % j == 0) {
			return 0;
		}	
	}
	return 1;
	
}

