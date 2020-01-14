#include <stdio.h>
#include <stdlib.h>

struct item {
	int key;
	int value;
	struct item* next;
};

struct item* table;

int hash(int key);
void put(int key, int value, int size);
int search(int key);

int main(int argc, char **argv) {
	/*File reader*/
	if (argc != 2) {
		printf("Insufficient Arguments\n");
		exit(0);
	}
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("File does not exist\n");
		exit(0);
	}
	table = (struct item*)malloc(1000 * sizeof(struct item));
	for (int i = 0; i < 1000; i++) {
		table[i].key = 0;
		table[i].value = 0;
		table[i].next = NULL;
	}
	/*Initialization*/
	int **matrix;
	int row;
	int col;
	int *r = &row;
	fscanf(fp,"%d", r);
	col = *r;
	int sqr = row * row;
	int size = 0;

	matrix = malloc(row * sizeof(int*));
	for (int k = 0; k < row; k++) {
		matrix[k] = malloc(col * sizeof(int));	
	}
	/*Traversing through file and doing initial checks*/
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int temp;
			int *tempVal = &temp;
			if (fscanf(fp, "%d", tempVal) > sqr) {
				printf("not-magic\n");
				return 0;
			}
			if (search(temp) == 1) {
				printf("not-magic\n");
				return 0;
			}
			put(temp,1,size);
			matrix[i][j] = temp;
		}
	}

	/*Sum Check*/
	int firstTravR = 1;
	int diagCheck; /*Used later, keeps track of magic sum of whole square*/
		int prevSum;
		int *prevP = &prevSum;	
		int currSum = 0;
		int *currP = &currSum;	
		/*SUMMING THE ROWS*/		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				currSum = currSum + matrix[i][j];
			}
			if (firstTravR == 1) {
				firstTravR = 0;	
			} else {
				if (prevSum != currSum) {
					printf("not-magic\n");
					return 0;
				} else {
					diagCheck = prevSum;
				}
			}
			*prevP = currSum;
			*currP = 0;
		}
		
		/*SUMMING THE COLUMNS*/
		int firstTravC = 1;		
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				currSum = currSum + matrix[j][i];
			}
			if (firstTravC == 1) {
				firstTravC = 0;
			} else {
				if (prevSum != currSum) {
					printf("not-magic\n");
					return 0;
				}
			}
			*prevP = currSum;
			*currP = 0;
		}
		
		/*SUMMING THE DIAGONALS*/
		for (int i = 0; i < row; i++) {
			currSum = currSum + matrix[i][i];
		}
		
		if (currSum == diagCheck) {
		} else {
			printf("not-magic\n");			
			return 0;
		}
		*currP = 0;

		/*SUMMING THE DIAGONALS REVERSE*/
		for (int i = (row - 1); i >= 0; i--) {
			currSum = currSum + matrix[i][i];
		}
		if (currSum == diagCheck) {
		} else {
			printf("not-magic\n");			
			return 0;
		}
	printf("magic\n");
	
	/* Freeing the Matrix */
	
	for (int k = 0; k < row; k++) {
		free(matrix[k]);
	}
	free(matrix);
	free(table);
	return 0;

}

/*Hash Table functions*/
int hash(int key) {
	return key % 1000;
}

void put(int key, int value, int size) {
	if (size > 1000) {
		return;	
	}	
	int index = hash(key);
	struct item* temp = NULL;
	temp = (struct item*)malloc(sizeof(struct item));
	temp->key = key;
	temp->value = value;
	struct item* nullCheck = &table[index];
	
	if (nullCheck != NULL) {
		temp->next = &table[index];
		table[index] = *temp;
		size++;
	} else if (table[index].value == value){
	} else {
		table[index] = *temp;
		size++;
	}
	
}

int search(int key) {
	int index = hash(key);
	if (table[index].key == key) {
		return 1;
	} else {
		return 0;
	}
}




