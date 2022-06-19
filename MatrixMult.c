void martixMartixMult(int matrix1[10][10], int matrix2[10][10], int result[10][10], int m1_rows, int m1_columns, int m2_rows, int m2_columns) {
    int i, j, k;
    if(m1_columns != m2_rows) 
        return -1;
    for(i = 0; i < m1_rows; i++) {
        for(j = 0; j < m2_columns; j++) {
            result[i][j] = 0;
            for(k = 0; k < m1_columns; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void matrixScalarMult(int matrix[10][10], int result[10][10], int scalar, int m_rows, int m_columns) {
    int i, j;
    for(i = 0; i < m_rows; i++) {
        for(j = 0; j < m_columns; j++) {
            result[i][j] = scalar * matrix[i][j];
        }
    }
}
