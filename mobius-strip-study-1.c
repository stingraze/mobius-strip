#include <stdio.h>
#define BUFFER_SIZE 10
//Created using the help of ChatGPT (GPT-4) on October 4th, 2023.
//(C)Tsubasa Kato at Inspire Search Corporation
//Please Visit Our Company Website at: https://www.inspiresearch.io/en
int main() {
    int buffer[BUFFER_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int mobiusTwist = 5;  // This is where our "twist" is located
    
    // Separate loop counter for 30 iterations
    for (int loopCounter = 0, index = 0; loopCounter < 30; loopCounter++) {
        // If we reach the twist, we "jump" to the beginning.
        if (index == mobiusTwist) {
            index = 0;
        }

        printf("Buffer[%d] = %d\n", index, buffer[index]);
        
        // Increment the buffer index for next iteration
        index = (index + 1) % BUFFER_SIZE;
        if (index % 5 == 0){
        	printf("Twisted at: %d\n", loopCounter + 1);
        }
    }

    return 0;
}
