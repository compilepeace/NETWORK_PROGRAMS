
//
//	Abhinav Thakur
//	compilepeace@gmail.com
//
//
//	program name: read_call.c
//	Description : This is a program to demonstrate read() call which reads the data from file 
//				  described by the file descriptor (fd) into a buffer. 
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd;
	char *buffer;
	struct stat stat_struct_var;

		
		// Checking for user-input 
		if (argc < 2)
		{
			printf("Usage: %s <filename> \n", argv[0]);
			exit(1);	
		}


			// opening the file
			fd = open(argv[1], O_RDONLY);


			// allocating space for file content to be read
			// For this we need the size of file. Use 
			// 'struct stat' if filename is known and
			// 'struct fstat' if you have file descriptor
			if (fstat(fd, &stat_struct_var) == -1) 
				perror("fstat(): ");
			
			
			printf("The size of file in bytes is: %d \n", stat_struct_var.st_size);
}	

