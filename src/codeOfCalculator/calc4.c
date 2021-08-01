#include "calc4PrintFunctions.h"
#include "calc3Helper.h"
#include <stdlib.h>

int main() {
    char op;
    float a1, a2;
    int boolVal;

    int firstEmptyPoint = 0;
    char historyOp[100];
    float historyVal[100][2];

    do {
        boolVal = 0;
        scanf(" %c", &op);
        // Can be *, /, +, -, a/A, s/S, p/P,c/C h/H.

        /**
         * Simple operations supported:
         *  * is for multiplication
         *  / is for division
         *  - is for subtraction
         *  + is for addition
         *
         * Complex operations supported:
         *  a/A for absolute difference
         *  p/P for a^b
         *  s/S for square root
         *  c/C for clear screen
         *  g/G for guiding
         *  h/H for printing the history
         */

        if (op == 'h' || op == 'H' || op == 'c' || op == 'C' || op == 'q' || op == 'Q') {
            // No operators here.
        } else if (op == 's' || op == 'S') {
            scanf("%f", &a1);
        } else {
            scanf("%f %f", &a1, &a2);
        }

        switch (op) { // Finding simple operations.
            case '*': {
                printf("%f\n", a1 * a2);
                boolVal = 1;
                break;
            } case '/': {
                printf("%f\n", a1 / a2);
                boolVal = 1;
                break;
            } case '-': {
                printf("%f\n", a1 - a2);
                boolVal = 1;
                break;
            } case '+': {
                printf("%f\n", a1 + a2);
                boolVal = 1;
                break;
            }
        }

        // Finding complex operations.
        if (op == 'a' || op == 'A') {
            printf("%f\n", absoluteDifference(a1, a2));
            boolVal = 1;
        } else if (op == 'p' || op == 'P') {
            printf("%d\n", aPowerB(a1, a2));
            // a^b assumes a and b to be int so returns int.
            boolVal = 1;
        } else if (op == 's' || op == 'S') {
            printf("%f\n", squareRoot(a1));
            boolVal = 1;
        } else if (op == 'c' || op == 'C') {
            #if defined(_WIN64) || defined(_WIN32) || defined(__CYGWIN__)
                system("cls");
            #else
                system("clear");
            #endif
            boolVal = 1;
            // NOTE: This command is for Windows only.
            // Mac/Linux use clear for this command.
        } else if (op == 'h' || op == 'H') {
            printHistory(historyOp, historyVal, firstEmptyPoint);
            boolVal = 1;
        } else if (op == 'q' || op == 'Q') {
            boolVal = 1;
        }

        if (boolVal) {
            // We wish that history only contains alphabets in lower case.
            if (op == 'A') {
                op = 'a';
            } else if (op == 'P') {
                op = 'p';
            } else if (op == 'S') {
                op = 's';
            } else if (op == 'H') {
                op = 'h';
            } else if (op == 'C') {
                op = 'c';
            }

            // Storing history.
            historyOp[firstEmptyPoint] = op;
            if (op != 'h' && op != 'c') {
                historyVal[firstEmptyPoint][0] = a1;
                if (op != 's') {
                    historyVal[firstEmptyPoint][1] = a2;
                }

            }
            // We want to increment the first empty point to store history at next point.
            firstEmptyPoint++;
        } else {
            // We do not want to store wrong operations in history.
            printf("Operation not supported\n");
            continue;
        }

    } while(op != 'Q' && op != 'q');

    return 0;
}
