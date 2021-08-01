#include <stdio.h>

void printHistory(char historyOperations[], float historyVal[][2], int firstEmptyPoint) {
    char op;

    for (int i = 0; i < firstEmptyPoint; i++) {
        op = historyOperations[i];
        printf("%c", op);
        if (op != 'h') { // If the operation is history, operators are not there so not printing them.
            printf(" on %f ", historyVal[i][0]);
            if (op != 's') { // S is square root which only takes one argument.
                printf("& %f", historyVal[i][1]);
            }
        }
        printf("\n");
    }
}
