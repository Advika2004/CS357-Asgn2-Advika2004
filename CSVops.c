/* this file holds all the functions needed to process the text file and create just an array of values to be graphed */

#include "CSVops.h"

/* function will open the given file, if it does not exist it will print an error*/
FILE* open_file(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        exit(-1);
    }
    return file;
}

/* This will just read each line from the file and store it in the buffer */
int read_line(FILE *file, char *buffer, int buffer_size){
    if (fgets(buffer, buffer_size, file)){
        buffer[strcspn(buffer, "\n")] = '\0'; 
        return 1;
    }
    return 0;
}

/* closes the file after done reading from it */
void close_file(FILE *file){
    fclose(file);
}

/* removes all spaces and tabs from the string */
void stripST(char *string){
    int string_length = strlen(string);
    int temp = 0;
    int i;
    for (i = 0; i < string_length; i++){
        if(!isspace(string[i])){
            string[temp] = string[i];
            temp++;
        }
    }
    string[temp] = '\0';
}

int countCommas(char *string){
    int string_length = strlen(string);
    int count = 0;
    int i;
    for (i = 0; i < string_length; i++){
        if(string[i] == ','){
            count++;
        }
    }
    return count;
}


void makeArrChunks(int arrayChunks[], char *string) {
    int numChunks = countCommas(string) + 1;
    long newChunk = 0; 
    char *currentPos = string;
    char *nextComma = NULL;
    int i = 0;

    while (i < numChunks) {
        nextComma = strchr(currentPos, ',');
        if (nextComma != NULL) {
            *nextComma = '\0'; 
        }

        if (*currentPos == '\0') {  
            newChunk = 0;
        } else {
            char *endptr;
            newChunk = strtol(currentPos, &endptr, 10);
            if (*endptr != '\0') {
                newChunk = 0; 
            }
        }

        arrayChunks[i] = (int)newChunk;
        if (nextComma != NULL) {
            *nextComma = ',';  
            currentPos = nextComma + 1; 
        }

        i++;
    }
}


int findSum(int arrayChunks[]){
    int i=0;
    int sum = 0;
    for (i=0; i < 1024; i++){
        sum += arrayChunks[i];
         /* printf("current sum: %d\n", sum); */
    }
    return sum;
}

void addSumToArr(int arrayOfSums[], int sum){
    static int i = 0;
    arrayOfSums[i] = sum;
    i++;
}


int findArraySize(char* string){
    int arraySize = 0;
    arraySize = countCommas(string) + 1;
    return arraySize;
}

int containsQuotes(char *string){
    if(strchr(string, '\"') != NULL){
        return 1;
    }

    if (strchr(string, '\'') != NULL) {
        return 1;
    }

    return 0;
}

int calculateStartIdx(int validElements){
    int skipVals = 1024 - validElements;
    return skipVals;
}

int findMin(int arrayOfSums[], int startIdx){
    int minval = arrayOfSums[startIdx];
    int i = startIdx;
    for (i = startIdx; i < 1024; i++){
        if(arrayOfSums[i] < minval){
            minval = arrayOfSums[i];
        }
    }
    return minval;
    }

int findMax(int arrayOfSums[], int startIdx){
    int maxval = arrayOfSums[startIdx];
    int i = startIdx;
    for (i = startIdx+1; i < 1024; i++){
        if(arrayOfSums[i] > maxval){
            maxval = arrayOfSums[i];
        }
    }
    return maxval;
    }

GraphStuff makeGraphData(int min, int max){
    GraphStuff empty;
    if (min < 0){
        empty.startinterv = (((min - 9)/ 10) * 10); /* where first bar is */
    } else {
        empty.startinterv = (((min+1) / 10) * 10); /* where first bar is */
    }
    if (max > 0){
        empty.endinterv = (((max + 9) / 10) * 10) ; /* where last bar is */
    } else {
        empty.endinterv = (((max) / 10) * 10) ; /* where last bar is */
    }
    empty.numBars = ((empty.endinterv - empty.startinterv) / 2) + 1; /* how many bars are there */
    return empty;
}


void makeFreqArr(int arrayOfFreq[], int startIdx, int arrayOfSums[], int* HOLD, int fileLineCount){
    int i = startIdx; /* where to start looking in array of sums */
    int intervIdx = 0; /* what bucket to put it in */
    int first_run = 1;
    int NonZeroNum = 0;

    for(i = startIdx; i < 1024; i++){
        if (first_run) {
            if(arrayOfSums[i] > 0){
                NonZeroNum++;
                intervIdx = calculatePosOffset(arrayOfSums, i);
                arrayOfFreq[intervIdx]++;
            } 
            else if (arrayOfSums[i] < 0){
                NonZeroNum++;
                intervIdx = calculateNegOffset(arrayOfSums, i);
                arrayOfFreq[intervIdx]++;
            }
            *HOLD = intervIdx;
            first_run = 0;
        }

        else {
            if(arrayOfSums[i] > 0){
                NonZeroNum++;
                intervIdx = calculatePosOffset(arrayOfSums, i);
                arrayOfFreq[intervIdx]++;
            } 
            else if (arrayOfSums[i] < 0){
                NonZeroNum++;
                intervIdx = calculateNegOffset(arrayOfSums, i);
                arrayOfFreq[intervIdx]++;
            }
        }     
    }
    arrayOfFreq[50] += fileLineCount - NonZeroNum;

}


int calculatePosOffset(int arrayOfSums[], int index){
    int intervIdx;
    intervIdx = 50 + ((arrayOfSums[index] + 1)/ 2);
    return intervIdx;
}

int calculateNegOffset(int arrayOfSums[], int index){
    int intervIdx;
    intervIdx = 50 + (arrayOfSums[index] / 2);
    return intervIdx;
}



/* now going to write the functions that should go into graphops.c under here */

int findNumDig(int number){
    if (number > 99 || number < -9){
        return 3;
    }
    if (number > 9 || number < 0){
        return 2;
    }
    return 1;
}

void printGraph(char *filename, GraphStuff example, int arrayOfFreq[], int max, int startFreq){
    int remainingLines;
    int graphHeight;
    int end;
    int numbLineDig;
    int spacesToAdd;
    int j;
    int digSpaces;
    int numberLineLength;
    int THISWORKS;
    FILE *file;
    graphHeight = 5 * ((max + 4) / 5);
    file = fopen(filename, "w");

    /* print out the beginning stuff */
    remainingLines = graphHeight + 1;
    while (remainingLines != 0){
        
        /* print out the left side of graph */
        int spacesToAdd;
        int digits;
        int i;
        int yAxisDigit;
        yAxisDigit = ((remainingLines / 5) * 5);
        digits = findNumDig(yAxisDigit);
        spacesToAdd = 3 - digits;
        if(remainingLines % 5 == 0){
            for (i = 0; i < spacesToAdd; i++){
                printf("%s", " ");
            }
            printf("%d", yAxisDigit);
            printf("%s", " T");
        }
        else {
            printf("%s", "    |");
        }

        /* print out the middle of graph */
        printf("%s", " ");
        THISWORKS = 50 + (example.startinterv/2);
        for (i = (example.startinterv/2) ; i < ((example.endinterv) / 2) + 1; i++){

            if (arrayOfFreq[startFreq] >= remainingLines){
                printf("%s", "#");
            }
            else{
                printf("%s", " ");
            }
            startFreq++;
        }
        startFreq = THISWORKS;

        /* print out the end of graph */
        printf("%s", " ");
        if (remainingLines % 5 == 0){
            printf("%s", "T ");
            printf("%d", yAxisDigit);
           /* printf("%s", "\n"); */
        }
        else{
            printf("%s", "|");
        }
        printf("%s", "\n");

         remainingLines = remainingLines - 1;
    }

    /* now printing out the axis */
    end = example.endinterv - example.startinterv;
    printf("%s", "    +-|");
    while (end > 0){
        printf("%s", "----|");
        end = end - 10;
    }
    printf("%s", "-+\n");


    /* now printing out numberline */
    numbLineDig = example.startinterv;
    
    numberLineLength = example.endinterv - example.startinterv;
    printf("%s", "  ");
    while(numberLineLength >= 0){
        digSpaces = findNumDig(numbLineDig);
        spacesToAdd = 5 - digSpaces;
        for(j = 0; j < spacesToAdd; j++){
            printf("%s", " ");
        }
        printf("%d", numbLineDig);
        numberLineLength = numberLineLength - 10;
        numbLineDig += 10;
    }
    printf("%s","\n");
    fclose(file);
}





















/*
int countFreq(int arrayOfSums[], int arraySize, int frequencyArray[]){
    int i = 0;
    int frequency = 0;
    int currentVal = arrayOfSums[i];
    for(i = 0; i < arraySize, i++){
        if(arrayOfSums[i] == currentVal){
            frequency++;
        }
    }
    frequencyArray[i] = frequency;
    i++;
    return frequency;
}
*/




/*
void makeArrChunks(char arrChunks[2048][2048], char *string){
    char *chunk;
    int i = 0;

    chunk = srtok(string, ",");
    while (chunk != NULL){
        strcpy(arrChunks[i], chunk);
        i++;
        chunk = strtok(NULL, ",");
    } 
    return;
}
*/
/*
void freeArrChunks(char** arrchunks){
    int i;
    for(i = 0; i < 2048; i++){
        free(arrchunks[i]);
    }
    free(arrchunks);
}
*/
/*
int main(void){
    const char *filename = "in5.txt";
    char buffer[2048];
    FILE *file = open_file(filename);
    int arrayChunks[1024] = {0};
    int arrayOfSums[1024] = {0};
    int frequencyArray[1024] = {0};   
    int arraySize = 0;  
    int sum = 0;
    int fileLineCount = 0;
    int i;
    int expectedCells = 0;

    if(read_line(file, buffer, sizeof(buffer))){
        expectedCells = countCommas(buffer) + 1;
        stripST(buffer);
    }
    else{
        printf("Empty file or cannot read the header.\n");
        close_file(file);
        exit(3);
    }

    while(read_line(file, buffer, sizeof(buffer))){
        if(containsQuotes(buffer) == 1){
            printf("./hist: Unsupported quotes\n");
            exit(2);
        }
        stripST(buffer);
        if (expectedCells != countCommas(buffer)+1){
            printf("./hist: Mismatched cells\n");
            close_file(file);
            exit(1);
        }
        fileLineCount++;
        printf("file line count: %d\n", fileLineCount);
        printf("processing line: %s\n", buffer);
        arraySize = findArraySize(buffer); 
        makeArrChunks(arrayChunks, buffer);
        sum = findSum(arrayChunks);
        addSumToArr(arrayOfSums, sum);
    }
    close_file(file);

    printf("All computed sums:\n");
    for (i = 0; i < fileLineCount; i++) {
        printf("Sum of line %d: %d\n", i, arrayOfSums[i]);
    }
    
    return 0;
}
*/
