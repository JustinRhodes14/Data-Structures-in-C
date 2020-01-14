#include <stdio.h>
#include <stdlib.h>

struct item {
	int key;
	int value;
	int empty; /*1 means index is empty (true), 0 means index is not empty (false)*/
	struct item* next;
};

struct item *table;



int hash(int key);
void put(int key, int value, int size);
int search(int key);

int main(int argc, char **argv) {

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
	int size = 0;

	for (int i = 0; i < 1000; i++) {
		table[i].key = 0;
		table[i].value = 0;
		table[i].empty = 1;		
		table[i].next = NULL;
		
	}
	
	char tempC;
	while (fscanf(fp, "%c\n", &tempC) != EOF) {		
		if (tempC == 'i') {
			int tempK;
			fscanf(fp, "%d", &tempK);
			put(tempK,tempK,size);
		} else if (tempC == 's') {
			int tempK;
			fscanf(fp,"%d", &tempK);			
			search(tempK);
		}
		
	}
	

	free(table);	
	return 0;

}


int hash(int key) {
	if (key < 0) {
		return (key * -1) % 1000;
	} else {
	return key % 1000;
	}
}

void put(int key, int value, int size) {
	if (size == 1000) {
		printf("table-full\n");
		return;	
	}	
	int index = hash(key);
	struct item* temp = NULL;
	temp = (struct item*)malloc(sizeof(struct item));
	temp->key = key;
	temp->value = value;
	struct item* nullCheck = &table[index];
	struct item* prev = NULL;
	prev = (struct item*)malloc(sizeof(struct item));
	if (nullCheck != NULL) {
		while (nullCheck != NULL) {
			if(nullCheck->value == value) {
				printf("duplicate\n");
				return;
			}	
			prev = nullCheck;		
			nullCheck = nullCheck->next;
		}
		prev->next = temp;	
		/*temp->next = &table[index];
		table[index] = *temp;*/
		size++;
		temp->empty = 0;
		printf("inserted\n");
	} else {
		table[index] = *temp;
		size++;
		temp->empty = 0;
		printf("inserted\n");
	}
	
}

int search(int key) {
	int index = hash(key);
	
	struct item* nullCheck = &table[index];	
	
	while (nullCheck != NULL) {
		if (nullCheck->key == key && nullCheck->empty != 1) {
		printf("present\n");
		return 1;
		}
		nullCheck = nullCheck->next;	
	}
		printf("absent\n");
		return 0;
	
}










