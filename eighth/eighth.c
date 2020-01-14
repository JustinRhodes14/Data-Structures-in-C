#include <stdio.h>
#include <stdlib.h>

struct treeNode {
	int value;
	struct treeNode* left;
	struct treeNode* right;
};

void insert(struct treeNode* ptr, int value);
void search(struct treeNode* ptr, int target);
void freeTree(struct treeNode* ptr);

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Insufficient Arguments\n");
		exit(0);
	}
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("error\n");
		exit(0);
	}
	
	struct treeNode* root = NULL;
	root = (struct treeNode*)malloc(sizeof(struct treeNode));
	root->value = 0;
	root->left = NULL;
	root->right = NULL;
	
	char holder;
	int firstInsert = 1;
	while (fscanf(fp,"%c",&holder) != EOF) {
		if (holder == 'i') {
			int temp;
			fscanf(fp,"%d",&temp);			
			if (firstInsert == 1) {
				root->value = temp;
				firstInsert = 0;
				printf("inserted 1\n");
			} else {
				insert(root,temp);	
			}
		} else if (holder == 's') {
			int temp;
			fscanf(fp,"%d",&temp);
			search(root,temp);
		}
	}
	
	freeTree(root);
	return 0;


}

void insert(struct treeNode* ptr, int value) {
	int left = 1;
	int count = 1;
	struct treeNode* prev = NULL;
	prev = (struct treeNode*)malloc(sizeof(struct treeNode));
	while (ptr != NULL) {
		if (ptr->value == value) {
			printf("duplicate\n");
			return;
		} else if (ptr->value > value) {
			prev = ptr;			
			ptr = ptr->left;
			count++;
			left = 1;
		} else {
			prev = ptr;			
			ptr = ptr->right;
			count++;
			left = 0;
		}
	}
	
	struct treeNode* temp = NULL;
	temp = (struct treeNode*)malloc(sizeof(struct treeNode));
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	if (left == 1) {
		prev->left = temp;
		printf("inserted %d\n", count);
	} else {
		prev->right = temp;
		printf("inserted %d\n", count);
	}
	return;
}

void search(struct treeNode* ptr, int target) {
	int count = 1;	
	while (ptr != NULL) {
		if (ptr->value == target) {
			printf("present %d\n",count);
			return;
		} else if (ptr->value > target) {		
			ptr = ptr->left;
			count = count + 1;
		} else {			
			ptr = ptr->right;
			count = count + 1;
		}
	}
		printf("absent\n");
		return;
}

void freeTree(struct treeNode* ptr) {
	if (ptr == NULL) {	
		return;
	}
	
	freeTree(ptr->left);
	freeTree(ptr->right);
	free(ptr);
}


















