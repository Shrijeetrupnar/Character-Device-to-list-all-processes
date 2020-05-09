# Character-Device-to-list-all-processes
Kernel Modules and Character Device to list all processes

C - program is written in C.
pipe.c - contains actual code
makefile- kindly run makefile to run the project


Author :
Shrijeet Rupnar (srupnar1@binghamton.edu) B-N0 : B00808280 
State University of New York, Binghamton


Implement a kernel module that creates a /dev/process_list character device. The character device should support the read() operation. When the read() system call is invoked on your character device from a user space process, your kernel module should return to the following information for all currently running processes:

process ID
parent process ID
the CPU on which the process is running
its current state.
For example, the output could be as follows:
	PID=1 PPID=0 CPU=4 STATE=TASK_RUNNING
	PID=2 PPID=0 CPU=2 STATE=TASK_INTERRUPTIBLE
	PID=10 PPID=2 CPU=0 STATE=TASK_UNINTERRUPTIBLE
	PID=16434 PPID=16424 CPU=10 STATE=TASK_DEAD
	PID=14820 PPID=16424 CPU=8 STATE=TASK_WAKEKILL,TASK_UNINTERRUPTIBLE
