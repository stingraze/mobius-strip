#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Created using ChatGPT (GPT-4) by Tsubasa Kato at Inspire Search Corporation.
//Visit: https://www.inspiresearch.io/en
#define ROWS 10
#define COLS 10
#define TARGET 35 
#define THRESHOLD 5 
#define MOBIUS_TWIST 5

double average(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (double)sum / size;
}

int main() {
    int array[ROWS][COLS];
    int validRows[ROWS], validCols[COLS];
    for (int i = 0; i < ROWS; i++) validRows[i] = 1;  
    for (int i = 0; i < COLS; i++) validCols[i] = 1;  
    int remainingRows = ROWS;
    int remainingCols = COLS;

    srand(time(NULL));

    printf("Initial Array:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            array[i][j] = rand() % 101;
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }

    for (int loopCounter = 0, index = 0; loopCounter < 30; loopCounter++) {
        if (loopCounter < MOBIUS_TWIST) {
            // Row-wise traversal before the twist
            if (validRows[index]) {
                printf("Row %d:\t", index + 1);
                for (int j = 0; j < COLS; j++) {
                    printf("%d\t", array[index][j]);
                }
                printf("\n");
            }
            index = (index + 1) % ROWS;
        } else {
            // Column-wise traversal after the twist
            if (validCols[index]) {
                printf("Col %d:\t", index + 1);
                for (int i = 0; i < ROWS; i++) {
                    printf("%d\t", array[i][index]);
                }
                printf("\n");
            }
            index = (index + 1) % COLS;
        }

        // Pruning logic for both rows and columns
        if (loopCounter == MOBIUS_TWIST) {
            for (int i = 0; i < ROWS; i++) {
                int row[COLS];
                for (int j = 0; j < COLS; j++) row[j] = array[i][j];
                if (validRows[i] && abs(average(row, COLS) - TARGET) > THRESHOLD) {
                    validRows[i] = 0;
                    remainingRows--;
                    printf("Pruned row %d (Avg: %.2f)\n", i + 1, average(row, COLS));
                }
            }
            for (int j = 0; j < COLS; j++) {
                int col[ROWS];
                for (int i = 0; i < ROWS; i++) col[i] = array[i][j];
                if (validCols[j] && abs(average(col, ROWS) - TARGET) > THRESHOLD) {
                    validCols[j] = 0;
                    remainingCols--;
                    printf("Pruned col %d (Avg: %.2f)\n", j + 1, average(col, ROWS));
                }
            }
        }

        // Check if any valid row has an average close enough to the TARGET
        if (loopCounter < MOBIUS_TWIST) {
            for (int i = 0; i < ROWS; i++) {
                int row[COLS];
                for (int j = 0; j < COLS; j++) row[j] = array[i][j];
                if (validRows[i] && abs(average(row, COLS) - TARGET) <= THRESHOLD) {
                    printf("TARGET REACHED on row %d (Avg: %.2f)\n", i + 1, average(row, COLS));
                    // Optionally, break or return here depending on desired behavior
                }
            }
        } else {
            // Check if any valid column has an average close enough to the TARGET
            for (int j = 0; j < COLS; j++) {
                int col[ROWS];
                for (int i = 0; i < ROWS; i++) col[i] = array[i][j];
                if (validCols[j] && abs(average(col, ROWS) - TARGET) <= THRESHOLD) {
                    printf("TARGET REACHED on col %d (Avg: %.2f)\n", j + 1, average(col, ROWS));
                    // Optionally, break or return here depending on desired behavior
                }
            }
        }
    }

    return 0;
}
