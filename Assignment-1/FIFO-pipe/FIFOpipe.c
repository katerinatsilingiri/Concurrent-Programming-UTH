#include <stdio.h>
#include <stdlib.h>
#include "FIFOpipe.h"
#include <pthread.h>

#define TRUE 1
#define FALSE 0


char* pipe;
volatile int readingPoint, writingPoint, sizeValue;
volatile int doneFlag;
int isempty;

// pipe_init
void pipe_init(int size) {
    int i;
    sizeValue = size;
    
    pipe = (char *)malloc(size * sizeof(char));
    if (pipe == NULL) {
        printf("ERROR. No allocated memory.\n");
    }
    
    readingPoint = 0;
    writingPoint = 0;
    doneFlag = 0;
    isempty=0;
    
    // Init the pipe with 0s
    for (i = 0; i < sizeValue; i++ ) {
        pipe[i] = 0;
    }
    
}


// pipe_write
void pipe_write(char c) {

    // writes data in pipe when the position is 0
    while(pipe[writingPoint] != 0){ 
        // Blocked
    }   

    pipe[writingPoint] = c;
    
    // Implementation of Ring-Buffer
    if (writingPoint == sizeValue - 1) { 
        writingPoint = 0; 
    }
    else {
        writingPoint = writingPoint + 1;
    }

    return;
}


// pipe_read
int pipe_read(char *c) {
    int i;
    isempty = 0;

    // Checks if the pipe is empty
    for (i = 0; i < sizeValue; i++) { 
        if (pipe[i] == 0) {
            isempty = isempty+1;
        }
    }
    
    // While there are no data in the pipe
    while(pipe[readingPoint] == 0) { 
        //blocked
        if((isempty == sizeValue) && (doneFlag == 1)) { 
            // Return when the pipe is empty and at the same time the writeDone is on
            return 0;
        }
    }

    // Case where there are data in the pipe
    *c = pipe[readingPoint];
    
    // When the data in the pipe are read, then they become equal to 0 
    pipe[readingPoint] = 0; 
   
    // Implementation of Ring-Buffer
    if(readingPoint == sizeValue - 1){
        readingPoint=0;
    }
     else {
         readingPoint= readingPoint + 1;
    }
 
    return 1;
}



// pipe_writeDone
void pipe_writeDone() {
    doneFlag = 1;
}


// pipe_destroy
void pipe_destroy(){
    free(pipe);
}





