// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

/* 

In /usr/include/netdb.h

struct addrinfo
{
  int ai_flags;                 // Input flags.  
  int ai_family;                // Protocol family for socket.  
  int ai_socktype;              // Socket type.  
  int ai_protocol;              // Protocol for socket.  
  socklen_t ai_addrlen;         // Length of socket address. 
  struct sockaddr *ai_addr;     // Socket address for socket.  
  char *ai_canonname;           // Canonical name for service location.  
  struct addrinfo *ai_next;     // Pointer to next in list.  
};



In /usr/include/netinet/in.h

// for IPv4
struct sockaddr_in
{
    __SOCKADDR_COMMON (sin_);
    in_port_t sin_port;             // Port number.  
    struct in_addr sin_addr;        // Internet address.  

    // Pad to size of `struct sockaddr'.  
    unsigned char sin_zero[sizeof (struct sockaddr) -
               __SOCKADDR_COMMON_SIZE -
               sizeof (in_port_t) -
               sizeof (struct in_addr)];
};

// Ditto, for IPv6.  
struct sockaddr_in6
{
    __SOCKADDR_COMMON (sin6_);
    in_port_t sin6_port;            // Transport layer port #
    uint32_t sin6_flowinfo;         // IPv6 flow information 
    struct in6_addr sin6_addr;      // IPv6 address 
    uint32_t sin6_scope_id;         // IPv6 scope-id 
};

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define FAMILY AF_UNSPEC
#define SOCKTYPE SOCK_STREAM
#define MAXSIZE 13

int main(int argc, char *argv[])
{
	struct addrinfo hints, *server_info = NULL;
	struct addrinfo *parser = NULL;
	int sockfd = 0, status = 0;


	// check for the command line args
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <HOSTNAME> <PORT>\n", argv[0]);
		exit(0x10);	
	}

	// fill in the server config to connect to and get them stored in struct addrinfo *server_info
	memset(&hints, 0, sizeof hints);
	hints.ai_family = FAMILY;
	hints.ai_socktype = SOCKTYPE;

	status = getaddrinfo(argv[1], argv[2], &hints, &server_info);
	if (status != 0x0)
	{
		fprintf(stderr, "getaddrinfo: ");
		exit(0x11);
	}

	// Parse through the search results (Linked list) and connect to the first we can
	for (parser = server_info; parser != NULL; parser = parser->ai_next)
	{
		// try creating a socket
		sockfd = socket(parser->ai_family, parser->ai_socktype, parser->ai_protocol);
		if (sockfd == -1)
		{
			perror("socket: ");
			continue;					// try creating a socket through next node
		}

		// try connecting to server
		status = connect(sockfd, parser->ai_addr, parser->ai_addrlen);
		if (status == -1)
		{
			perror("connect: ");
			continue;					// Try through the next node in linked list
		}

		break;
	}


	if (parser == NULL)
	{
		fprintf(stderr, "client: failed to conect after parser reached NULL (end of linked list)\n");
		exit(0x12);
	}

	void *raw_ip;
	char ip_string[INET6_ADDRSTRLEN];

	
	// If IPv4 is IPv4, convert from network to presentation form
	if (parser->ai_addr->sa_family == AF_INET)
	{
		raw_ip = &( ((struct sockaddr_in *)(parser->ai_addr))->sin_addr );
		inet_ntop(parser->ai_family, raw_ip , ip_string, sizeof ip_string);
		printf("Client: connected to %s\n", ip_string);
	}

	// If family is IPv6, convert from network to presentation form
	else 
	{
		raw_ip = &( ((struct sockaddr_in6 *)(parser->ai_addr))->sin6_addr );
		inet_ntop(parser->ai_family, raw_ip, ip_string, sizeof ip_string);
		printf("Client: connected to %s\n", ip_string);
	}
		
	freeaddrinfo(server_info);

	
	char buffer[16];
	unsigned int *pointer = NULL, *pointerx = NULL;
	unsigned int bytes_recieved = 0, bytes_sent = 0;
	unsigned int counter = 0, counterx = 0;
	unsigned int return_value = 0;
	uint64_t sum = 0; 



	// recieving 16 bytes(4 unsingned ints) in host byte order from server
	bytes_recieved = recv(sockfd, buffer, 16, 0x0);

	printf("Recieved %d bytes\n", bytes_recieved);
	printf("\n-=-=-=-=-= Values Recieved (in Network Byte Order) =-=-=-=-=-\n\n");	
	for(pointerx = (unsigned int *)buffer; counterx < 4; ++counterx, ++pointerx)
	{
		printf("[-]Valuex%d : 0x%x\n", counterx+1, *pointerx);
	}

	printf("\n-=-=-=-=-= Values Converted (in Host Byte Order) =-=-=-=-=-\n\n");	
	for (pointer = (unsigned int *)buffer; counter < 4; ++counter, ++pointer )
	{
		return_value = ntohl( (uint32_t )(*pointer) );
		sum += return_value;
		printf("[+]Value%d : 0x%x\n", counter+1, return_value);
	}

	
	// Converting sum to big endian
    printf("\nsum is : 0x%lx : %d\n", sum, sizeof sum);
	
	void *payload = (void *)&sum;	

	printf("final payload : %s\n", payload);
	send(sockfd, payload, sizeof payload, 0);
	printf("\n0x%lx -----", *((uint64_t *)payload));

	
	char result[500];
	recv(sockfd, (void *)result, 500, 0);


return 0;
}



