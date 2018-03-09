/*
  
  

  
##########	Abhinav Thakur
##########	compilepeace@gmail.com
  
########## 	Program name - web_client.c
##########	Description  - This is a web client program which sends HTTP request to a web server



				STRUCTURES USED

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Structure describing a generic socket address.
// In /usr/include/bits/socket.h  

struct sockaddr
  {
    __SOCKADDR_COMMON (sa_);	// Common data: address family and length.  
    char sa_data[14];			// Address data.  
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Structure describing an internet socket address (IP address/ Port # / Domain-AF_INET...)
// In /usr/include/netinet/in.h

struct sockaddr_in
  {
    __SOCKADDR_COMMON (sin_);
    in_port_t sin_port;				// Port number. 
    struct in_addr sin_addr;		// Internet address. 

    // Pad to size of `struct sockaddr' (which is a generic socket address structure).  
    unsigned char sin_zero[sizeof (struct sockaddr) -
			   __SOCKADDR_COMMON_SIZE -
			   sizeof (in_port_t) -
			   sizeof (struct in_addr)];
  };

.......................................................

// Ditto, for IPv6.  
struct sockaddr_in6
  {
    __SOCKADDR_COMMON (sin6_);
    in_port_t sin6_port;		// Transport layer port # 
    uint32_t sin6_flowinfo;		// IPv6 flow information 
    struct in6_addr sin6_addr;	// IPv6 address 
    uint32_t sin6_scope_id;		// IPv6 scope-id 
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// Types of sockets in /usr/include/bits/socket_type.h

enum __socket_type
{
  SOCK_STREAM = 1,		// Sequenced, reliable, connection-based
				   		// byte streams. 
#define SOCK_STREAM SOCK_STREAM
  SOCK_DGRAM = 2,		// Connectionless, unreliable datagrams
				   		//   of fixed maximum length.  
#define SOCK_DGRAM SOCK_DGRAM
...
};

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Description of data base entry for a single host.  

struct hostent
{
  char *h_name;						// Official name of host.  
  char **h_aliases;					// Alias list.  
  int h_addrtype;					// Host address type.  
  int h_length;						// Length of address.  
  char **h_addr_list;				// List of addresses from name server.  
#ifdef __USE_MISC
# define	h_addr	h_addr_list[0]  // Address, for backward compatibility.
#endif
};
 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




				FUNCTIONS PROTOTYPES
				
##	/usr/include/sys/socket.h

->	socket(int domain, int type, int protocol)				
->	connect(int fd, struct sockaddr *remote_host, socklen_t addr_length)
->	bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
->	listen(int fd, int backlog_queue_size)
->	accept(int fd, struct sockaddr *remote_host, socklen_t *addr_length)
->	send(int fd, void *buffer, size_t n, int flags)
->	recv(int fd, void *buffer, size_t n, int flags)

##	/usr/include/netinet/in.h

->	htonl(long value)
->	htons(short value)
->	ntohl(long value)
->	ntohs(short value)		

##	/usr/include/arpa/inet.h

->	inet_aton(char *ascii_addr, struct in_addr *network_addr)
->	inet_ntoa(struct in_addr *network_addr)								

##	/usr/include/netdb.h

->	gethostbyname(char *hostname)			// Returns a pointer to 'hostent' structure
		



^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*/		



#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PORT 80


int main(int argc, char *argv[])
{
	struct sockaddr_in host_address;
	struct hostent *host_info;
	int socket_fd, test;
	char request[2000], response[2000];

	

		// Checking if domain name is provided
		if (argc < 2)
		{
			printf("Usage: %s <domain_name> \n", argv[0]);
			exit(1);
		}

				
		
			// dns resolution
			host_info = gethostbyname(argv[1]);
			if (host_info == NULL)
			{
				printf("Error while dns resolution: gethostbyname() \n");
				exit(1);
			}



				// Creating a socket
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				if (socket_fd == -1)
				{
					printf("Error while creating a socket: socket() \n");
					exit(1);
				}
				


				// filling up host_address structure 
				host_address.sin_family = AF_INET;
				host_address.sin_port = htons(PORT);
				host_address.sin_addr = *((struct in_addr *)(host_info->h_addr));


				// connecting to the host
				test = connect(socket_fd, (struct sockaddr *)&host_address, sizeof(struct sockaddr));
				if (test == -1)
				{
					printf("Error while connecting to the host: connect() \n");
					exit(1);
				}		
				// printf("DEBUG: connected to host: %s \n", inet_ntoa(host_address.sin_addr));



					// sending request
					gets(request);
					send(socket_fd, request, strlen(request), 0);
					recv(socket_fd, response, sizeof(response), 0);
			
		
					printf("%s\n", response);						


}
