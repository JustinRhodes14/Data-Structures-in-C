#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int rows, int cols);
int** mult_matrix(int** m1, int** m2,int** m3, int row1, int col2,int sim);
void print_matrix(int** matrix, int row, int col);
void free_matrix(int** matrix, int row, int col);

int** allocate_matrix(int rows, int cols) {
	int** matrix = malloc(rows * sizeof(int*));	
	for(int i = 0; i < rows; i++) {
		matrix[i] = malloc(cols * sizeof(int));
	}
	return matrix;
}

int** mult_matrix(int** m1, int** m2,int** m3, int row1, int col2, int sim) {
	int sum = 0;
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col2; j++) {
			for (int g = 0; g < sim; g++) {
				sum = sum + m1[i][g] * m2[g][j];
			}
			m3[i][j] = sum;
			sum = 0;
		}
	}
	return m3;
}

void free_matrix(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

void print_matrix(int** matrix, int row, int col) {
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			printf("%d	", matrix[i][j]);
		}
		printf("\n");
	}
}
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
	
	int row1;
	int col1;
	int *r1 = &row1;
	int *c1 = &col1;
	fscanf(fp,"%d", r1);
	fscanf(fp,"%d", c1);
	
	
	int **matrix1 = allocate_matrix(row1,col1);
	for (int i = 0; i < row1; i++) {
		for (int j = 0; j < col1; j++) {		
			fscanf(fp,"%d",&matrix1[i][j]);
		}
	}
	int row2;
	int col2;
	int *r2 = &row2;
	int *c2 = &col2;
	fscanf(fp,"%d", r2);
	fscanf(fp,"%d", c2);
	if (col1 != row2) {
		printf("bad-matrices\n");
		exit(0);
	}
	
	
	int **matrix2 = allocate_matrix(row2,col2);
	for (int i = 0; i < row2; i++) {
		for (int j = 0; j < col2; j++) {		
			fscanf(fp,"%d",&matrix2[i][j]);
		}
	}
	int ** matrix3 = allocate_matrix(row1,col2);
	matrix3 = mult_matrix(matrix1,matrix2,matrix3,row1,col2,row2);
	print_matrix(matrix3,row1,col2);
	
	free_matrix(matrix1,row1,col1);
	free_matrix(matrix2,row2,col2);
	free_matrix(matrix3,row1,col2);
	
	return 0;
	

}













