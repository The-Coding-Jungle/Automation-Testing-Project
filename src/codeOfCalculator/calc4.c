#include "calc4PrintFunctions.h"
#include "calc3Helper.h"

int main() {
    char inputFiles[3][100] = {"../../data/Inputs/1.txt", "../../data/Inputs/2.txt", "../../data/Inputs/3.txt"};
    char outputFiles[3][100] = {"../../data/RealOutputs/1.txt", "../../data/RealOutputs/2.txt", "../../data/RealOutputs/3.txt"};

    FILE* inputFile;
    FILE* outputFile;

    char* buffer;
    int bufferLen;

    char op;
    float a1, a2;
    int boolVal;

    int firstEmptyPoint = 0;
    char historyOp[100];
    float historyVal[100][2];

    for (int i = 0; i < 3; i++) {

        inputFile = fopen(inputFiles[i], "r");
        outputFile = fopen(outputFiles[i], "w");

        do {
            boolVal = 0;
            buffer = getMyLine(inputFile, &bufferLen);
            sscanf(buffer, "%c", &op);
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
                buffer = getMyLine(inputFile, &bufferLen);
                sscanf(buffer, "%f", &a1);
            } else {
                buffer = getMyLine(inputFile, &bufferLen);
                sscanf(buffer, "%f %f", &a1, &a2);
            }

            switch (op) { // Finding simple operations.
                case '*': {
                    fprintf(outputFile, "%f\n", a1 * a2);
                    boolVal = 1;
                    break;
                } case '/': {
                    fprintf(outputFile, "%f\n", a1 / a2);
                    boolVal = 1;
                    break;
                } case '-': {
                    fprintf(outputFile, "%f\n", a1 - a2);
                    boolVal = 1;
                    break;
                } case '+': {
                    fprintf(outputFile, "%f\n", a1 + a2);
                    boolVal = 1;
                    break;
                }
            }

            // Finding complex operations.
            if (op == 'a' || op == 'A') {
                fprintf(outputFile, "%f\n", absoluteDifference(a1, a2));
                boolVal = 1;
            } else if (op == 'p' || op == 'P') {
                fprintf(outputFile, "%d\n", aPowerB(a1, a2));
                // a^b assumes a and b to be int so returns int.
                boolVal = 1;
            } else if (op == 's' || op == 'S') {
                fprintf(outputFile, "%f\n", squareRoot(a1));
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
                printHistory(outputFile, historyOp, historyVal, firstEmptyPoint);
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

        fclose(inputFile);
        fclose(outputFile);
    }
    return 0;
}
