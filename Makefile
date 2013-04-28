SOURCES := main.c vm.c value.c
OBJECTS=${SOURCES:.c=.o}
CC=gcc
EXECUTABLE=vlisp
WEBHTML=vlisp.html

all: local 

local: CC=clang
local: CFLAGS:=-g -c -Wall
local: LDFLAGS= 
local: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	

#web: CC=clang
#web: CCFLAGS=-S -emit-llvm
#web: $(SOURCES) $(WEBHTML)

web: 
	emcc $(SOURCES) -o $(WEBHTML)


	
clean:
	@echo "Cleaning..."
	@rm -rf *.html *.bc *.s *.ll *.o vlisp

.PHONY: all clean local
