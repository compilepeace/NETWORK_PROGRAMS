# Network_programming
 
  Hey there, this repository contains network programs demonstrating TCP/IP client-server model. This is not
  supposed to be a great rather its a just for fun project which started out of curiosity to understand
  how the network programming worked in the purest form with C programming language. It could have been done
  with other high level programming languages also (like java, python etc.) but the layers of abstraction
  languages like python provide won't let me have an insight about the concept.
  I would love any suggestions on how can this model be made better or
  any contributions regarding the same would be appreciated.
  Cheers,


# USAGE
Just compile the source code - "Webserver/web_server.c".
Issue the commands bellow on the linux command line to generate and ELF executable of webserver-
	
	$ git clone https://github.com/compilepeace/Network_programming/	# clonning git repository
	$ cd Network_programming/Webserver					# getting into Webserver directory
	$ gcc web_server.c -o webserver						# compiling webserver
	$ ./webserver 								# running webserver

To compile the web_client, issue the bellow commands-

	$ cd ./../web_client/							# getting to web_client directory 
	$ gcc web_client.c -o webclient  					# compiling webclient
