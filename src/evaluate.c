#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char bool;
enum {false, true};

bool compareStrings(char* a, char* b) {
    int lenA = strlen(a), lenB = strlen(b);

    if (lenA != lenB) {
        return false;
    } else {
        for (int i = 0; i < lenA; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        } return true;
    }
}

char* strip(char* str, int* len) {
    while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n') {
        str++;
        (*len)--;
    }

    while (str[*len - 1] == ' ' || str[*len - 1] == '\t' || str[*len - 1] == '\n') {
        (*len)--;
        str[*len] = '\0';
    }
    return str;
}

void printTestCaseAndExit(char* inputFileName, FILE* inF, FILE* outF) {
    FILE* inputFile = fopen(inputFileName, "r");
    char arr[100];

    while (fgets(arr, 100, inputFile)) {
        printf("%s", arr);
    }
    fclose(inputFile);
    fclose(inF);
    fclose(outF);
    exit(0);
}

int main() {
    char realOutputFileNames[3][100] = {"../data/RealOutputs/1.txt", "../data/RealOutputs/2.txt", "../data/RealOutputs/3.txt"};
    char outputFileNames[3][100] = {"../data/Outputs/1.txt", "../data/Outputs/2.txt", "../data/Outputs/3.txt"};
    char inputFileNames[3][100] = {"../data/Inputs/1.txt", "../data/Inputs/2.txt", "../data/Inputs/3.txt"};

    FILE* inputFile;
    FILE* outputFile;

    char* buffer1 = (char*) malloc(sizeof(char) * 100);
    char* buffer2 = (char*) malloc(sizeof(char) * 100);
    int buffer1Len = 0, buffer2Len = 0;

    #if defined(_WIN32) || defined(__CYGWIN__) 
        system(".\toExecute.bat");
    #else 
        system("./toExecute.sh");
    #endif

    for (int i = 0; i < 3; i++) {
        inputFile = fopen(realOutputFileNames[i], "r");
        outputFile = fopen(outputFileNames[i], "r");

        while ((fgets(buffer1, 100, inputFile) != NULL) && (fgets(buffer2, 100, outputFile) != NULL)) {
            buffer1Len = strlen(buffer1);
            buffer2Len = strlen(buffer2);

            buffer1 = strip(buffer1, &buffer1Len);
            buffer2 = strip(buffer2, &buffer2Len);

            if (!compareStrings(buffer1, buffer2)) {
                printf("The case #%d has failed\n", i + 1);
                printTestCaseAndExit(inputFileNames[i], inputFile, outputFile);
            }        
        }

        char buff1End = getc(inputFile);
        char buff2End = getc(outputFile);

        if (buff1End == EOF && buff2End == EOF) {
            printf("Passed testcase #%d.\n", i + 1);
        } else {
            printf("The case #%d has failed\n", i + 1);
            printTestCaseAndExit(inputFileNames[i], inputFile, outputFile);
        }

        fclose(inputFile);
        fclose(outputFile);
    }

    return 0;
}