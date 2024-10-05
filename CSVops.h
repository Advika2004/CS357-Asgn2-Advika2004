#ifndef CSVops_H
#define CSVops_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct GraphStuff{
    int startinterv;
    int endinterv;
    int numBars;
}GraphStuff;


FILE* open_file(const char *filename);
int read_line(FILE *file, char *buffer, int buffer_size);
void close_file(FILE *file);
void stripST(char *string);
int countCommas(char *string);
void makeArrChunks(int arrayChunks[], char *string);
int findSum(int arrayChunks[]);
void addSumToArr(int arrayOfSums[], int sum);
int findArraySize(char* string);
int containsQuotes(char *string);
int calculateStartIdx(int validElements);
int findMin(int arrayOfSums[], int startIdx);
int findMax(int arrayOfSums[], int startIdx);
GraphStuff makeGraphData(int min, int max);
void makeFreqArr(int arrayOfFreq[], int startIdx, int arrayOfSums[], int* HOLD, int fileLineCount);
void printGraph(char *filename, GraphStuff example, int arrayOfFreq[], int max, int startFreq);
int calculatePosOffset(int arrayOfSums[], int index);
int calculateNegOffset(int arrayOfSums[], int index);
void removeHyphens(char *str);

#endif