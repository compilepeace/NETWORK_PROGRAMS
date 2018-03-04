//
//	Abhinav Thakur
//	compilepeace@gmail.com
//
//
//	program name: strtok.c
//	Description : This program was made while working for web_server.c, This program demonstrates the
//				  usage of strtok(), which helped me a lot while handling user HTTP requests, which 
//				  otherwise would have made the program a bit complicated (since I would then use 
//				  pointers to segregate request tokens.
//
//				  Usage: strtok(char *buffer, const char *delimiter)
//				  It breaks the buffer into individual tokens seperated by the delimiter string (which
//				  the user provides in the bellow example). It does so by adding NULL charecters in 
//				  place of each delimiter string, so if you need the original string don't use strtok
//				  this makes it unfit for use in multithreaded programs since any process would 
//				  make change to the original string.
//
//				  For eg: strtok(buffer, " ,:;|")			// all of the charecters ' ', ',', ':', ';', '|'
//				  											// will be treated as delimiters.
//
//				  


#include <stdio.h>
#include <string.h>


int main()
{
	char request[20] = "GET / HTTP/1.0";
	char *tokens[3];
	int i=0;

		tokens[0] = strtok(request, " ");			// will break the sentence with ' ' as delimiters
		tokens[1] = strtok(NULL, " ");				// Next time it remembers where it left off i.e. why not
		tokens[2] = strtok(NULL, " ");				// required the buffer address to be given


		// for loop to print all tokens
   		for (i = 0 ; i < 3 ; ++i)	
			printf("Token[%d] = %s \n", i, tokens[i]);	


return 0;	
}
