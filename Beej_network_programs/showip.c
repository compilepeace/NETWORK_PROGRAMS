// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

/* 

In /usr/include/netdb.h

struct addrinfo
{
  int ai_flags;					// Input flags.  
  int ai_family;				// Protocol family for socket.  
  int ai_socktype;				// Socket type.  
  int ai_protocol;				// Protocol for socket.  
  socklen_t ai_addrlen;			// Length of socket address. 
  struct sockaddr *ai_addr;		// Socket address for socket.  
  char *ai_canonname;			// Canonical name for service location.  
  struct addrinfo *ai_next;		// Pointer to next in list.  
};



In /usr/include/netinet/in.h

// for IPv4
struct sockaddr_in
{
    __SOCKADDR_COMMON (sin_);
    in_port_t sin_port;				// Port number.  
    struct in_addr sin_addr;		// Internet address.  

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
    in_port_t sin6_port;			// Transport layer port #
    uint32_t sin6_flowinfo;			// IPv6 flow information 
    struct in6_addr sin6_addr;		// IPv6 address 
    uint32_t sin6_scope_id;			// IPv6 scope-id 
};

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define FAMILY AF_UNSPEC
#define SOCKTYPE SOCK_STREAM


int main(int argc, char *argv[])
{
	struct addrinfo hints, *server_info;
	struct addrinfo *ptr = NULL;
	int status;
	char ipstr[INET6_ADDRSTRLEN];


	// check for the command line args
	if (argc < 2)
	{
		printf("Usage: %s <domain_name>\n", argv[0]);
		return 0x10;
	}

	// zero out the structure provided_info initially and fill in the
	// ai_family and ai_socktype members of provided_info structure.
	memset( &hints, 0, sizeof hints );	
	hints.ai_family = FAMILY;			
	hints.ai_socktype = SOCKTYPE;

	// getaddrinfo() returning the resulting linked list of struct addrinfo to 'server_info'
	status = getaddrinfo(argv[1], NULL, &hints, &server_info);
	if (status != 0)
	{
		fprintf(stderr, "%s\n", gai_strerror(status));
		exit(0x11);
	}

	// parse through linked list and print the IP addresses of
	// the struct addrinfo linked lists returned
	for (ptr = server_info; ptr != NULL; ptr = ptr->ai_next)
	{
		char *ip_version;
		void *ip_address;
		
		// check if the family is IPv4
		if (ptr->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)ptr->ai_addr;
			ip_address = &(ipv4->sin_addr);
			ip_version = "IPv4";
		}

		// the family is IPv6
		else
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)ptr->ai_addr;
			ip_address = &(ipv6->sin6_addr);
			ip_version = "IPv6";	
		}

		inet_ntop( ptr->ai_family, ip_address, ipstr, sizeof ipstr);	
		printf("%s: %s\n", ip_version, ipstr);
	}

	freeaddrinfo(server_info);	

return 0;
}
