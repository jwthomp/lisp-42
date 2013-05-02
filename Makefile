SOURCES := main.c vm.c
VALUE_SOURCES := values/cons.c values/number.c values/nil.c values/process.c values/bytecode.c values/symbol.c values/string.c
SOURCES += $(VALUE_SOURCES)
OBJECTS=${SOURCES:.c=.o}
CC=gcc
EXECUTABLE=vlisp
WEBHTML=vlisp.html
ODIR=$(PWD)/objs
DEPS := value.h values/values.h vm.h

OBJ = $(patsubst %,$(ODIR)/%,$(OBJECTS))

all: init
all: local 


init:
	mkdir -p $(PWD)/objs/values

local: CC=clang
local: CFLAGS:=-g -c -Wall
local: LDFLAGS= 
local: value.h values/values.h vm.h
local: $(EXECUTABLE)
local: $(EXECUTABLE)


$(EXECUTABLE): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


#web: CC=clang
#web: CCFLAGS=-S -emit-llvm
#web: $(SOURCES) $(WEBHTML)

web: 
	emcc $(SOURCES) -o $(WEBHTML)


	
clean:
	@echo "Cleaning..."
	@rm -f *.html *.bc *.s *.ll *.o vlisp
	@rm -rf objs
	@rm -f values/*.o

.PHONY: all clean local
