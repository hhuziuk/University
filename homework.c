#include <iostream>
#include <time.h>
#include <stdlib.h>

int** allocate2D(int rows, int cols)
{
    int** arr2D;
    int i;
    arr2D = (int**)malloc(rows * sizeof(int*));
    for (i = 0; i < rows; i++)
    {
        if (arr2D != NULL)
            arr2D[i] = (int*)malloc(cols * sizeof(int));
    }
    return arr2D;
}

void deallocate2D(int** arr2D, int rows)
{
    int i;
    for (i = 0; i < rows; i++)
    {
        free(arr2D[i]);
    }
    free(arr2D);
}

void fillMatrix(int** matrix, int rows, int cols) {
    int i, j;
    srand(time(NULL));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}

void matrixScanner(FILE* thisFile, int** array, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            fscanf_s(thisFile, "%d", &array[i][j]);
    }
}

void arrayMultiply(int** arr1, int** arr2, int** arr3, int c1, int r1, int c2, int r2) {
    printf_s("third: \n");
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            arr3[i][j] = 0;
            for (int a = 0; a < c1; a++) {
                arr3[i][j] += arr1[i][a] * arr2[a][j];
            }
            printf_s("%d ", arr3[i][j]);
        }
        printf_s("\n");
    }

}

void matrixOutput(int** array, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf_s("%d ", array[i][j]);
        }
        printf_s("\n");
    }
}

void matrixToFile(FILE* thisFile, int** array, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            fprintf(thisFile, "%d ", array[i][j]);
        }
        fprintf(thisFile, "\n");
    }
}

int main()
{
    FILE* myFile, * myFile2, * myFile3;
    myFile = fopen("C:\\Users\\hh53872\\Desktop\\homework\\matrix1.txt", "w+");
    myFile2 = fopen("C:\\Users\\hh53872\\Desktop\\homework\\matrix2.txt", "w+");
    myFile3 = fopen("C:\\Users\\hh53872\\Desktop\\homework\\matrix3.txt", "w");
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    int i = 0, j = 0;
    srand(time(0));

    printf_s("Enter the number of rows for the first matrix: ");
    scanf_s("%d", &r1);
    printf_s("Enter the number of columns for the first matrix: ");
    scanf_s("%d", &c1);

    printf_s("Enter the number of rows for the second matrix: ");
    scanf_s("%d", &r2);
    printf_s("Enter the number of columns for the second matrix: ");
    scanf_s("%d", &c2);

    int** array1 = allocate2D(r1, c1);
    int** array2 = allocate2D(r2, c2);
    int** array3 = allocate2D(r1, c2);

    fillMatrix(array1, r1, c1);
    fillMatrix(array2, r2, c2);

    if (myFile == NULL && myFile2 == NULL && myFile3 == NULL) {
        printf("File read error\n");
    }

    matrixScanner(myFile, array1, r1, c1);
    matrixScanner(myFile, array1, r2, c2);
    matrixScanner(myFile2, array2, r2, c2);

    if (r1 == c2) {
        printf_s("\n");
        matrixOutput(array1, r1, c1);
        printf_s("\n");
        matrixOutput(array2, r2, c2);
        arrayMultiply(array1, array2, array3, c1, r1, c2, r2);
    }
    else
        printf_s("wrong values in rows or columns");

    fprintf(myFile, "%d %d\n", r1, c1);
    fprintf(myFile2, "%d %d\n", r2, c2);

    matrixToFile(myFile, array1, r1, c1);
    matrixToFile(myFile2, array2, r2, c2);
    matrixToFile(myFile3, array3, r1, c2);

    fclose(myFile);
    fclose(myFile2);
    fclose(myFile3);

    deallocate2D(array1, r1);
    deallocate2D(array2, r2);
    deallocate2D(array3, r1);

    return 0;
}