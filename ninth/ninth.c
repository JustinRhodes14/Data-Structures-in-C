#include <stdio.h>
#include <stdlib.h>

/*BST W/ DELETE FUNCTION*/
struct treeNode {
	int value;
	struct treeNode* left;
	struct treeNode* right;
};

void insert(struct treeNode* ptr, int value);
int search(struct treeNode* ptr, int target);
void delete(struct treeNode* prev, struct treeNode* ptr, int target);
struct treeNode* successor(struct treeNode* ptr);

struct treeNode* root;

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
			if (search(root,temp) != 0) {
				printf("present %d\n",search(root,temp));
			} else {
				printf("absent\n");
			}
		} else if (holder == 'd') {
			int temp;
			fscanf(fp,"%d",&temp);
			delete(NULL,root,temp);
		}
	}
	freeTree(root);
	return 0;


}

void insert(struct treeNode* ptr, int value) {
	int left = 1;
	int count = 1;
	struct treeNode* prev = NULL;
	if (ptr == NULL) {
		struct treeNode* temp = NULL;
		temp = (struct treeNode*)malloc(sizeof(struct treeNode));
		temp->value = value;
		temp->left = NULL;
		temp->right = NULL;
		ptr = temp;
		printf("inserted %d\n",count);
		return;
	}
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

int search(struct treeNode* ptr, int target) {
	int count = 1;	
	while (ptr != NULL) {
		if (ptr->value == target) {
			return count;
		} else if (ptr->value > target) {		
			ptr = ptr->left;
			count = count + 1;
		} else {			
			ptr = ptr->right;
			count = count + 1;
		}
	}
		return 0;
}

void delete(struct treeNode* prev, struct treeNode* ptr, int target) {
	int left = 0;	
	while (ptr != NULL) {
		if (ptr->value == target) {
			break;
		} else if (ptr->value > target) {
			prev = ptr;			
			ptr = ptr->left;
			left = 1;
		} else {
			prev = ptr;			
			ptr = ptr->right;
			left = 0;
		}
	}
	
	if (ptr == NULL) {
		printf("fail\n");
		return;
	} else if (prev == NULL) {
		if (ptr->right != NULL && ptr->left == NULL) {			
			root = ptr->right;
			free(ptr);
			printf("success\n");
			return;
		} else if (ptr->left != NULL && ptr->right == NULL) {
			root = ptr->left;
			free(ptr);
			printf("success\n");
			return;
		} else if (ptr->left == NULL && ptr->right == NULL){
			root = NULL;
			printf("success\n");
			return;
		} else {
			struct treeNode* temp = successor(ptr);
	
			root->value = temp->value;
			delete(root,root->right,temp->value);
		}
	} else if (ptr->right == NULL && ptr->left !=NULL) {
		if (left == 1) {		
			prev->left = ptr->left;
			free(ptr);
			printf("success\n");
			return;
		} else {
			prev->right = ptr->left;
			free(ptr);
			printf("success\n");
			return;
		}
	} else if (ptr->left == NULL && ptr->right != NULL) {
		if (left == 1) {		
			prev->left = ptr->right;
			free(ptr);
			printf("success\n");
			return;
		return;
		} else {
			prev->right = ptr->right;
			free(ptr);
			printf("success\n");
			return;
		}
	} else if (ptr->left == NULL && ptr->right == NULL) {
		if (prev == NULL) {
			free(ptr);			
			printf("success\n");
			return;
		} else if (left == 1) {
			prev->left = NULL;
			free(ptr);
			printf("success\n");
			return;
		} else {
			prev->right = NULL;
			free(ptr);
			printf("success\n");
			return;
		}
	} else {
		struct treeNode* temp = successor(ptr);
	
			ptr->value = temp->value;
			delete(ptr,ptr->right,temp->value);
	}
	return;
}

struct treeNode* successor(struct treeNode* ptr) {
	struct treeNode* temp2 = ptr->right;
				while (temp2->left != NULL) {
					temp2 = temp2->left;
				}
	return temp2;
}
void freeTree(struct treeNode* ptr) {
	if (ptr == NULL) {	
		return;
	}
	freeTree(ptr->left);
	freeTree(ptr->right);
	free(ptr);
}



