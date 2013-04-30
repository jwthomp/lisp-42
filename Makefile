SOURCES := main.c vm.c process.c
VALUE_SOURCES := values/cons.c values/number.c values/nil.c values/process.c values/bytecode.c values/symbol.c values/string.c
SOURCES += $(VALUE_SOURCES)
OBJECTS=${SOURCES:.c=.o}
CC=gcc
EXECUTABLE=vlisp
WEBHTML=vlisp.html

all: local 

local: CC=clang
local: CFLAGS:=-g -c -Wall
local: LDFLAGS= 
local: value.h values/values.h vm.h
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
	@rm -f *.html *.bc *.s *.ll *.o vlisp
	@rm -f values/*.html values/*.bc values/*.s values/*.ll values/*.o

.PHONY: all clean local
