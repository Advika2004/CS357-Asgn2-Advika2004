#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CSVops.h"


int compare(const void *x, const void *y){
    int xval = *(int *)x;
    int yval = *(int *)y;
    return xval - yval;
}


int main(void){
    char buffer[2048];
    FILE *file = stdin;
    int arrayChunks[1024] = {0};
    int arrayOfSums[1024] = {0};
    int arrayOfFreq[1024] = {0}; 
    int sum = 0;
    int fileLineCount = 0;
    int expectedCells = 0;
    int min = 1000;
    int max = -1000;
    int frequencyMax = 0;
    int HOLD = 0;
    GraphStuff example;
    example.startinterv = 0;
    example.endinterv = 0;
    example.numBars = 0;

    if(read_line(file, buffer, sizeof(buffer))){
        expectedCells = countCommas(buffer) + 1;
        stripST(buffer);
    }
    else{
        printf("Empty file or cannot read the header.\n");
        close_file(file);
        return 3;
    }

    while(read_line(file, buffer, sizeof(buffer))){
        if(containsQuotes(buffer) == 1){
            printf("./hist: Unsupported quotes\n");
            return 2;
        }
        stripST(buffer);
        if (expectedCells != countCommas(buffer)+1){
            printf("./hist: Mismatched cells\n");
            return 1;
        }
        fileLineCount++;
        /* arraySize = findArraySize(buffer); */
        makeArrChunks(arrayChunks, buffer);
        sum = findSum(arrayChunks);
        if (sum > max){
            max = sum;
        }
        if (sum < min){
            min = sum;
        }
        addSumToArr(arrayOfSums, sum);
    }
    qsort(arrayOfSums, 1024, sizeof(int), compare);
    example = makeGraphData(min, max);
    makeFreqArr(arrayOfFreq, 0, arrayOfSums, &HOLD, fileLineCount);
    frequencyMax = findMax(arrayOfFreq, 0);


    printGraph("test.txt", example, arrayOfFreq, frequencyMax, HOLD);

    close_file(file);
    return 0;
}

