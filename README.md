# Vulnerable Network Programming 
 
  Hey there, this repository demonstrates the "Network Programming" concepts (TCP/IP client-server model) with the help of programs
  which are intensionally made vulnerable to various binary exploitation techniques. This started out of curiosity to understand how
  the network programs worked at the purest form with C programming language and hence is made vulnerable. It could have been  
  implemented in other high level programming languages also (like java, python etc.) but the layers of abstraction provided by 
  languages like python provide won't let us have an insight about the concepts.
  I would love any suggestions on how can this model be made more vulnerable and any contributions regarding the same would be
  appreciated.
  Cheers,


## USAGE
Just compile the source code - "Webserver/web_server.c".
Issue the commands bellow on the linux command line to generate and ELF executable of webserver-
	
	$ git clone https://github.com/compilepeace/Network_programming/	# clonning git repository
	$ cd Network_programming						# getting into Networ_programming directory
	$ make									# building webserver, webclient and dnsresolver
	$ make run_webserver 							# run the webserver on port 8080
		

## VULNERABILITIES
 - Buffer Overflow
 - Local File Inclusion (LFI)


#### Note : Ignore the warnings since the "webserver" program is intensionally made vulnerable so that later on Exploitation can be demonstrated.

