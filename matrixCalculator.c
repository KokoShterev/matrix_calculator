#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

#define MAX_DIM 5

void printMatrix(int n, float matrix[][MAX_DIM])
{
	for (int i = 1; i < n; i++){
	    for (int j = 1; j < n; j++){
		    printf("%f\t", matrix[i][j]);
	    }
	    printf("\n");
	}
}
void swapRows(int row1, int row2, int n, float matrix[][MAX_DIM]){
	float t;
    for (int j = 1; j < n; j++){
        t = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = t;
    }
}
void division(int n, float divisor, float source[][MAX_DIM], float destination[][MAX_DIM])
{
    if (divisor == 0){
        printf("Division by zero is not allowed!\n");
    } else {
    	for (int i = 1; i < n; i++){
    	    for (int j = 1; j < n; j++){
                destination[i][j] = source[i][j] / divisor;
    	    }
    	}
    }
}
void transposition(int n, float source[][MAX_DIM], float destination[][MAX_DIM])
{
	for (int i = 1; i < n; i++){
	    for (int j = 1; j < n; j++){
            destination[i][j] = source[j][i];
	    }
	}
}
float determinant(int n, float original[][MAX_DIM]){
    float matrix[MAX_DIM][MAX_DIM];
    int swapCount = 0;
	for (int i = 1; i < n; i++){
	    for (int j = 1; j < n; j++){
            matrix[i][j] = original[i][j];
	    }
	}
    for(int i = 1; i < n-1; i++){
        int isSwapped = 0;
        for (int j = i+1; j < n; j++){
            //Swap rows if matrix[i][i] == 0
            if (matrix[i][i] == 0){
                for(int j = i + 1; j < n; j++){
                    if(matrix[j][i] != 0){
                        swapRows(i, j, n, matrix);
                        swapCount++;
                        isSwapped = 1;
                        // printf("%i, %i\n", i, j);
                        break;
                    }
                }
                if (isSwapped == 0)
                    return 0;
            }
            float c = 0 - matrix[j][i]/matrix[i][i];
            for (int k = 1; k < n; k++){
                matrix[j][k] = matrix[i][k] * c + matrix[j][k];
            }
        }
    }
    float det = 1;
    for (int i = 1; i < n; i++)
        det *= matrix[i][i];
    // printf("%i\n", swapCount);
    return pow(-1, swapCount) * det;
}
float adjugate(int i, int j, int n, float matrix[][MAX_DIM]){
    float adjugateMatrix[MAX_DIM][MAX_DIM] = {0};
    int i2 = 1;
    for (int i1 = 1; i1 < n; i1++){
        if (i1 != i){
            int j2 = 1;
    	    for (int j1 = 1; j1 < n; j1++){
    	        if(j1 != j){
    	            adjugateMatrix[i2][j2] = matrix[i1][j1];
	            } else {
	                j2--;
	            }
	            j2++;
    	    }
        } else {
            i2--;
        }
        i2++;
	}
	return pow(-1, (i+j)) * determinant(n-1, adjugateMatrix);
}
void inversion(int n, float source[][MAX_DIM], float destination[][MAX_DIM]){
    float det = determinant(n, source);
    if (det == 0){
        printf("The matrix has no inverse. Its determinant is zero!\n");
    } else {
        for (int i = 1; i < n; i++){
    	    for (int j = 1; j < n; j++){
                destination[j][i] = adjugate(i, j, n, source) / det;
    	    }
	    }
    }
}
int main()
{
    srand((unsigned) time(NULL));
	int n = 5;
    // float matrix[MAX_DIM][MAX_DIM] = {0};
    // for (int i = 1; i < n; i++){
	//     for (int j = 1; j < n; j++){
    //         matrix[i][j] = rand() % 21 - 10;
	//     }
	// }
    float matrix[MAX_DIM][MAX_DIM] = {
        {0,0,0,0,0},
        {0,0,0,0,1},
        {0,1,0,0,0},
        {0,0,1,0,0},
        {0,0,0,1,0}
    };
    printMatrix(n, matrix);
    printf("\n");
    printf("%f\n", determinant(n, matrix));
    printf("\n");
    float destination[MAX_DIM][MAX_DIM] = {0};
    inversion(n, matrix, destination);
    // division(n, 4, matrix, destination);
    // transposition(n, matrix, destination);
    printMatrix(n, destination);
    // printMatrix(n, matrix);

	return 0;
}