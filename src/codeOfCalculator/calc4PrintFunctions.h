#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHistory(FILE* outputFile, char historyOperations[], float historyVal[][2], int firstEmptyPoint) {
    char op;

    for (int i = 0; i < firstEmptyPoint; i++) {
        op = historyOperations[i];
        fprintf(outputFile, "%c", op);
        if (op != 'h' && op != 'c') { // If the operation is history, operators are not there so not printing them.
            fprintf(outputFile, " on %f ", historyVal[i][0]);
            if (op != 's') { // S is square root which only takes one argument.
                fprintf(outputFile, "& %f", historyVal[i][1]);
            }
        }
        fprintf(outputFile, "\n");
    }
}

char* getMyLine(FILE* inputFile, int* len) {
    char* line = (char*) malloc(sizeof(char) * 100);
    fgets(line, 100, inputFile);
    // Getting the raw line.

    *len = strlen(line);
    // Getting length of the line.

    while (line[0] == ' ' || line[0] == '\t' || line[0] == '\n') {
        line++;
        (*len)--;
    }

    while (line[(*len) - 1] == ' ' || line[(*len) - 1] == '\t' || line[(*len) - 1] == '\n') {
        (*len)--;
        line[*len] = '\0';
    }

    return line;
}