#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char str);
void stringSwapper(char *c,char *temp, int length);

int main(int argc, char **argv) {
	
	if (argc < 2) {
		printf("insufficient-arguments\n");
		exit(0);
	}
	
	int stringLength = 0;
	
	int bound = argc;
	for (int i = 1; i < argc; i++) {
		stringLength = stringLength + strlen(argv[i]);
	}
	
	stringLength = stringLength * 3;
	int firstPass = 1;
	for (int j = 1; j < bound; j++) {
		int strLen = (strlen(argv[j]) + 4);
		char *temp;
		temp = malloc(strLen * sizeof(char));
		if (isVowel(argv[j][0]) == 1) {
			strcpy(temp,argv[j]);
			strcat(temp,"yay");	
		} else {
			char *t;
			t = malloc(strLen * sizeof(char));
			int count = 0;
			while (isVowel(argv[j][count]) != 1 && count < strLen) {
				t[count] = argv[j][count];				
				count = count + 1;
			}
			int i = 0;
			int tempCounter = 0;
			for (i = count; i < (strLen - 4); i++) {		
				temp[tempCounter] = argv[j][i];	
				tempCounter++;
			}
			strcat(temp,t);
			strcat(temp,"ay");
			count = 0;
		}
		if (firstPass == 0) {		
			printf(" %s ", temp);
		} else {
			printf("%s ", temp);
			firstPass = 1;
		}
		free(temp);
		
	}
	printf("\n");
	
	return 0;
}

int isVowel(char str) {
	if (str == 'a' || str == 'e' || str == 'i' || str == 'o' || str == 'u' || str == 'A'|| str == 'E' || str == 'I' || str == 'O' || str == 'U') {		
		return 1;
	}	
	return 0;
}

void stringSwapper(char* c,char *temp, int length) {
	char *t = &c[0];
	for (int i = 1; i < length; i++) {
		char *temC = &c[i];		
		strcat(temp,temC);	
	}
	strcat(temp,t);
}










