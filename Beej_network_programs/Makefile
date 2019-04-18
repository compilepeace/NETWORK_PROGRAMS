

.PHONY: clean

T1= showip
T2= client
TARGETS= $(T1) $(T2) 

all: $(TARGETS)


$(T1): $(T1).c
	gcc $< -o $@

$(T2): $(T2).c
	gcc $< -o $@

clean:
	rm $(TARGETS)
