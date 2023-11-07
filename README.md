# OS_PROJECT

Here is my code for solving the producer consumer problem.
This code was written in linux and compiled using the GNU build. 
The main purpose of this code is to have the producer function produce a number to send to the buffer.
Then the consumer will consume each product placed in the buffer by the producer.
I implemented semaphores for waiting to see if the buffer has room to produce and continuing if so.
I also implemented mutex locks to lock the buffer when the functions are in progress and unlock when they are done.

the command for compiling the code is as follows:
gcc pc.cpp

the command for running the code is:
./runner
