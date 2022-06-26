#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_DIM 5

void printMatrix(int n, float matrix[][MAX_DIM]) {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
}
void swapRows(int row1, int row2, int n, float matrix[][MAX_DIM]) {
    float t;
    for (int j = 1; j < n; j++) {
        t = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = t;
    }
}
void division(int n, float divisor, float source[][MAX_DIM], float destination[][MAX_DIM]) {
    if (divisor == 0) {
        printf("Division by zero is not allowed!\n");
    } else {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                destination[i][j] = source[i][j] / divisor;
            }
        }
    }
}
void transposition(int n, float source[][MAX_DIM], float destination[][MAX_DIM]) {
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            destination[i][j] = source[j][i];
        }
    }
}
float determinant(int n, float original[][MAX_DIM]) {
    float matrix[MAX_DIM][MAX_DIM];
    int swapCount = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            matrix[i][j] = original[i][j];
        }
    }
    for (int i = 1; i < n - 1; i++) {
        int isSwapped = 0;
        for (int j = i + 1; j < n; j++) {
            //Swap rows if matrix[i][i] == 0
            if (matrix[i][i] == 0) {
                for (int j = i + 1; j < n; j++) {
                    if (matrix[j][i] != 0) {
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
            float c = 0 - matrix[j][i] / matrix[i][i];
            for (int k = 1; k < n; k++) {
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
float adjugate(int i, int j, int n, float matrix[][MAX_DIM]) {
    float adjugateMatrix[MAX_DIM][MAX_DIM] = {
        0
    };
    int i2 = 1;
    for (int i1 = 1; i1 < n; i1++) {
        if (i1 != i) {
            int j2 = 1;
            for (int j1 = 1; j1 < n; j1++) {
                if (j1 != j) {
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
    return pow(-1, (i + j)) * determinant(n - 1, adjugateMatrix);
}
void inversion(int n, float source[][MAX_DIM], float destination[][MAX_DIM]) {
    float det = determinant(n, source);
    if (det == 0) {
        printf("The matrix has no inverse. Its determinant is zero!\n");
    } else {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                destination[j][i] = adjugate(i, j, n, source) / det;
            }
        }
    }
}

void martixMartixMult(float matrix1[][MAX_DIM], float matrix2[][MAX_DIM], float result[][MAX_DIM], int m1_rows, int m1_columns, int m2_rows, int m2_columns) {
    int i, j, k;
    if (m1_columns != m2_rows)
        return -1;
    for (i = 0; i < m1_rows; i++) {
        for (j = 0; j < m2_columns; j++) {
            result[i][j] = 0;
            for (k = 0; k < m1_columns; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void matrixScalarMult(float matrix[][MAX_DIM], float result[][MAX_DIM], int scalar, int m_rows, int m_columns) {
    int i, j;
    for (i = 0; i < m_rows; i++) {
        for (j = 0; j < m_columns; j++) {
            result[i][j] = scalar * matrix[i][j];
        }
    }
}

int main() {
    // srand((unsigned) time(NULL));
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
        {0,0,0,1,0}};
    float matrix2[MAX_DIM][MAX_DIM] = {
        {0,0,0,0,0},
        {0,0,0,0,2},
        {0,3,0,0,0},
        {0,0,4,0,0},
        {0,0,0,5,0}};
    // printMatrix(n, matrix);
    // printf("\n");
    // printf("%f\n", determinant(n, matrix));
    // printf("\n");
    float destination[MAX_DIM][MAX_DIM] = {0};
    // inversion(n, matrix, destination);
    // // division(n, 4, matrix, destination);
    // // transposition(n, matrix, destination);
    // printMatrix(n, destination);
    // // printMatrix(n, matrix);

    printf("To get matrix from file enter 'F'\nTo get matrix from the console enter 'C'\n");
    char option1;
    scanf("%c", & option1);
    if (option1 == 'F' || option1 == 'f') {
        //chetene ot file
    } else if (option1 == 'C' || option1 == 'c') {
        //chetene ot konzola
    } else {
        printf("invalid choice");
    }

    int option2;
    while (1) {
        system("cls||clear");
        printf("1. Умножение на матрица със скалар\n");
        printf("2. Умножение на матрица с матрица\n");
        printf("3. Намиране на детерминанта на матрица с размери до 4х4\n");
        printf("4. Деление на матрица по скалар\n");
        printf("5. Намиране на обратна матрица\n");
        printf("6. Транспониране на матрица\n");
        printf("7. Exit\n");
        scanf("%i", & option2);

        if (option2 == 1) {
            //Умножение на матрица със скалар
            int scalar;
            printf("Enter a multiplier\n");
            scanf("%i", & scalar);
            matrixScalarMult(matrix, destination, scalar, n, n);
            printMatrix(n, destination);
        } else if (option2 == 2) {
            //Умножение на матрица с матрица
            martixMartixMult(matrix, matrix2, destination, n, n, n, n);
            printMatrix(n, destination);
        } else if (option2 == 3) {
            //Намиране на детерминанта на матрица с размери до 4х4
            printf("%f\n", determinant(n, matrix));
        } else if (option2 == 4) {
            //Деление на матрица по скалар
            int divisor;
            printf("Enter a divisor: ");
            scanf("%i", & divisor);
            division(n, divisor, matrix, destination);
            printMatrix(n, destination);
        } else if (option2 == 5) {
            //Намиране на обратна матрица
            inversion(n, matrix, destination);
            printMatrix(n, destination);
        } else if (option2 == 6) {
            //Транспониране на матрица
            transposition(n, matrix, destination);
            printMatrix(n, destination);
        } else if (option2 == 7) {
            return 0;
        } else {
            printf("invalid choice");
        }
        printf("Press enter to continue\n");
        getchar();
        getchar();
    }

    return 0;
}