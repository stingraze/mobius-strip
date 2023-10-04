#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define TARGET 35 //Change this target
#define THRESHOLD 5 // Allowed difference from target
#define MOBIUS_TWIST 5

double rowAverage(int arr[COLS]) {
    int sum = 0;
    for (int i = 0; i < COLS; i++) {
        sum += arr[i];
    }
    return (double)sum / COLS;
}

int main() {
    int array[ROWS][COLS];
    int validRows[ROWS];
    for (int i = 0; i < ROWS; i++) validRows[i] = 1;  // Initialize all rows as valid
    int remainingRows = ROWS;

    // Seed for random number generation
    srand(time(NULL));

    // Fill the array with random numbers between 0 and 100
    printf("Initial Array:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            array[i][j] = rand() % 101;
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }

    // Möbius strip-inspired iteration and pruning process
    for (int loopCounter = 0, rowIndex = 0; loopCounter < 30; loopCounter++) {
        // If we reach the twist, start pruning
        if (rowIndex == MOBIUS_TWIST && remainingRows > 1) {
            for (int i = 0; i < ROWS; i++) {
                if (validRows[i] && abs(rowAverage(array[i]) - TARGET) > THRESHOLD) {
                    validRows[i] = 0;
                    remainingRows--;
                    printf("Pruned row %d (Avg: %.2f)\n", i, rowAverage(array[i]));
                }
            }
        }

    // Check if any valid row has an average close enough to the TARGET
    for (int i = 0; i < ROWS; i++) {
        if (validRows[i] && abs(rowAverage(array[i]) - TARGET) <= THRESHOLD) {
            printf("TARGET REACHED on row %d (Avg: %.2f)\n", i + 1, rowAverage(array[i]));  // Add 1 to the row number
            break;
        }
    }

    // Print current row if it's valid
    if (validRows[rowIndex]) {
        printf("Row %d:\t", rowIndex + 1);  // Add 1 to the row number
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", array[rowIndex][j]);
        }
        printf("\n");
    }

        // Move to next row or reset to the beginning if at the twist
        rowIndex = (rowIndex + 1) % ROWS;
    }

    return 0;
}
