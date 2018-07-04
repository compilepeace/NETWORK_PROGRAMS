/*
  
  

  
##########	Abhinav Thakur
##########	compilepeace@gmail.com
  
##########  Program name - dns_resolver.c 
##########	Description  - It takes in domain name as argument and prints out its 
						   corresponding IP address.



				STRUCTURES USED

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


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


^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
				

##	/usr/include/arpa/inet.h

->	inet_aton(char *ascii_addr, struct in_addr *network_addr)
->	inet_ntoa(struct in_addr *network_addr)								

##	/usr/include/netdb.h

->	gethostbyname(char *hostname)			// Returns a pointer to 'hostent' structure
		



^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

*/		



#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	struct hostent *target_address;
	struct in_addr *address;	
	
	
		if (argc < 2)
		{
			printf("Usage: %s <domain_name>\n", argv[0]);
			exit(EXIT_FAILURE);
		}


		// gethostbyname() takes in a domain name as argument
		//  and returns a pointer to hostent structure storing 
		//  the IP address of the domain name in network byte order,
		target_address = gethostbyname(argv[1]);	
		

			// Now that target address info is stored in hostent structure
			// pointed to by 'target_address' pointer, we can show this 
			// to the user.
			// for sake of simplicity, we do this in 2 steps 
			// 
			// First accessing the 'h_addr' member of the hostent structure 
			// (storing the IP address in network byte order) and typecasting
			// the address into in_addr type (see struct sockaddr_in). 
			// 
			// Finally converting it into ascii notation before printing it !
			//
			address = (struct in_addr *)(target_address->h_addr);
			printf("%s has IP address : %s\n", argv[1], inet_ntoa(*address));

return 0;
}






















