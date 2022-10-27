main:  FIFOpipe.o mainThread.c 
	gcc -Wall -g  mainThread.c FIFOpipe.o -o main -lpthread

	
FIFOpipe.o: FIFOpipe.c FIFOpipe.h
	gcc -Wall -g -c FIFOpipe.c -o FIFOpipe.o -lpthread
clean:
	rm *.o
	rm main
