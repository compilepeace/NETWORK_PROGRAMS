
BUILD_DIR_WEBSERVER=./Webserver
BUILD_DIR_WEBCLIENT=./web_client
BUILD_DIR_DNSRESOLVER=./DNSresolver



all: webserver webclient dnsresolver

.PHONY: clean



webserver:
	make -C $(BUILD_DIR_WEBSERVER)

webclient:
	make -C $(BUILD_DIR_WEBCLIENT)

dnsresolver:
	make -C $(BUILD_DIR_DNSRESOLVER)
	


clean:
	make -C $(BUILD_DIR_WEBSERVER) clean
	make -C $(BUILD_DIR_WEBCLIENT) clean 
	make -C $(BUILD_DIR_DNSRESOLVER) clean
