#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

int insertOrderly(struct Node* prev, struct Node* ptr,int num);
int deleteNode(struct Node* prev, struct Node* ptr, int num);
void freeList(struct Node* ptr);

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
	
	struct Node* front = NULL;
	char tempC;
	int tempNum;
	int nodeCount = 0;
	struct Node* prev = NULL;
	while (fscanf(fp, "%c\n", &tempC) != EOF) {
		prev = NULL;
		if (tempC == 'i') {
			fscanf(fp,"%d\n",&tempNum);
			if (front == NULL) {
				front = (struct Node*)malloc(sizeof(struct Node));
				front->data = tempNum;
				nodeCount++;
			} else if (front->data > tempNum) {
				struct Node* temp = NULL;
				temp = (struct Node*)malloc(sizeof(struct Node));
				temp->data = tempNum;
				temp->next = front;
				front = temp;
				nodeCount++;
			} else if (insertOrderly(prev,front,tempNum) == 1) {
				nodeCount++;
			}
			
		} else if (tempC == 'd') {
			fscanf(fp,"%d\n", &tempNum);
			int *tempP = &tempNum;
			if (front != NULL && front->data == tempNum) {
				front = front->next;
				nodeCount = nodeCount - 1;
			} else if (deleteNode(prev,front,*tempP) == 1) {				
				nodeCount = nodeCount - 1;
			}
		}
		
	}
	int *countP = &nodeCount;
	printf("%d\n",*countP);
	while (front != NULL) {
		printf("%d	", front->data);
		front = front->next;
	}
	freeList(front);
	printf("\n");
	return 0;
}

int insertOrderly(struct Node* prev, struct Node* ptr, int num) {
		struct Node* temp = NULL;
		temp = (struct Node*)malloc(sizeof(struct Node));
		temp->data = num;
		while (ptr != NULL && ptr->data < num) {		
			prev = ptr;		
			ptr = ptr->next;
		}
		if (ptr != NULL && ptr->data == num) {
			return 0;
		} else if (prev == NULL) {	
			temp->next = (ptr);
			ptr = temp;
			return 1;
		} else {		
			temp->next = prev->next;
			prev->next = temp;
			return 1;
		}
}

int deleteNode(struct Node* prev, struct Node* ptr, int num) {
	if (ptr == NULL) {
		return 0;
	}

	while (ptr != NULL && ptr-> data != num) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == NULL) {
		return 0;
	} else {
	prev->next = ptr->next;
	free(ptr);
	return 1;
	}
}
void freeList(struct Node* ptr) {
	struct Node* temp = ptr;
	while (temp != NULL) {
		struct Node* temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
}








