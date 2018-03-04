//
//	Abhinav Thakur
//	compilepeace@gmail.com
//
//
//	program name: open_call.c
//	Description : This is a program to demonstrate opening of file and if file does not exit create it
//				  You can also install errno tool which can tell you which error code means what . Just
//				  issue the command "apt-get install errno" on Ubuntu systems.
//
//
//	**	A bit of Theoritical knowledge
//	
//	1.	File Descriptor Table : It is a collection of integer array indices (called as file descriptors)
//								on which (indices) the value stored are pointers to 'file table entries'
//								(which are structures).
//								Each process has its unique 'file descriptor table'.
//
//	2.	File table entries	  : These are structures made created when a process requests to open a file.
//								These entries maintain the 'file positions'. i.e. why open() returns a
//								file descriptor, value at which (in file descriptor table) is a reference
//								to file table entry for that particular 'file descriptor'. 
//								Therefore, we can say that indirectly the file descriptor keeps a track 
//								on file position.
//
//	
//				  When 'fd = open()' is called, it returns a file descriptor i.e. 'fd', if file is 
//				  opened up by 2 file descriptors, i.e. something like this
//
//				  		int fd1 = open("abhinav.txt", O_RDONLY);
//				  		int fd2 = open("abhinav.txt", O_RDONLY);
//
//				  then each file descriptor has its own open "file table entry" and each file descriptor
//				  has its own position for "abhinav.txt" when it reads some amount of data in file ( via
//				  read() ).	
//

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

extern int errno;

int main()
{
	int fd;

		
		fd = open("abhinav.txt", O_RDONLY | O_CREAT);
		
		printf("File Descriptor: %d \n", fd);

		// if open function fails
		if (fd == -1)
		{
			printf("Error code: %d \n", errno);
			perror("open(): ");
		}

	// close the file descriptor not in use	
	close(fd);
		
return 0;
}
