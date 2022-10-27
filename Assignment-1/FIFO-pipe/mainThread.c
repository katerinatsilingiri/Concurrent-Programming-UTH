#include <stdio.h>
#include "FIFOpipe.h"
#include <pthread.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

volatile char* pipe;
FILE *finalFile, *initialFile;
int readDoneFlag; // Indicates that myRead() has terminated 
int writeDoneFlag; // Indicates that myWrite() has terminated

void *myRead(){
    char ch;

    // The contents of the pipe are written in the final.txt file 
    finalFile=fopen("final.txt", "w");
   
    // While pipe_read reads successfully from the pipe, the data are written to the final.txt file 
    while(pipe_read(&ch)!=0) {
        fprintf(finalFile,"%c",ch);
    }
    
    readDoneFlag = TRUE;
    fclose(finalFile);

    return 0;
    
}

void *myWrite(void *arg){
    char character;

    // The contents of the initial.txt are read and written to the pipe 
    initialFile = fopen("initial.txt","r");

    if (initialFile == NULL)
    {
        printf("File is not available \n");
        exit(-1);
    }
    
    while (1) {
        character = fgetc(initialFile);
        if (character == EOF) { // Stop writting in the pipe when the end of the file has been reached
            pipe_writeDone();  
            break;
        }
        pipe_write(character);
    }

    // Wait while myRead() still runs
    while(readDoneFlag == FALSE);
    
    writeDoneFlag = TRUE;
    fclose(initialFile);

    pipe_destroy();
    return 0;
    
}

// main thread
int main (int argc, char *argv[]) {  
    
    int size = atoi(argv[1]);
    
    if (size <= 0) {
        printf("ERROR. Enter a valid size\n");
        return(0);
    }
    
    int res1, res2;
    pthread_t readingThread, writingThread;
    
    // initialization
    readDoneFlag = FALSE;
    writeDoneFlag = FALSE;
    pipe_init(size);
    
    // Create the threads
    res1 = pthread_create(&writingThread, NULL, myWrite, NULL);
    if (res1) {
        printf("ERROR: return code from pthread_create() is %d\n", res1);
        exit(-1);
    }
    res2 = pthread_create(&readingThread, NULL, myRead, NULL);
     if (res2) {
        printf("ERROR: return code from pthread_create() is %d\n", res2);
        exit(-1);
    }
    
    // Wait until myRead() terminates
    while (readDoneFlag == FALSE);

    return(0);
}
