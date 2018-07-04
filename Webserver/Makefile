

.PHONY: clean run_webserver

webserver: web_server.c send_recieve.h
	gcc $< -o $@



run_webserver:
	./webserver

clean:
	rm webserver
