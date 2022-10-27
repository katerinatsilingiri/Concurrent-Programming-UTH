1.1 FIFO Pipe 
- This program uses a FIFO pipe (of one direction) for the communication of two threads and has the following 
functions:
    - pipe_init() : Initialization of the FIFO pipe with a selected size
    - pipe_write() : Writes One Byte to the FIFO pipe
    - pipe_WriteDone() : Indicates the termination of the writing of the data 
    - pipe_read() : Reads one Byte 
    - pipe_destroy() : Destroys the FIFO pipe
- If the pipe is full, the function pipe_write() "is blocked" and cannot run until there is empty space in the pipe. 
    Similarly, if the pipe is empty, the function pipe_read() "is blocked" and cannot run untile there are some data in the pipe.
    If the data are read successfully, pipe_read() returns 1. If the pipe is empty and the function pipe_writeDone() is done, pipe_read() returns 0.
- For this program, the method of Ring-Buffer is used.
    
