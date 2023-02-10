CC=gcc
INCLUDEDIR=. ./includes
LIBSDIR= . 
BINARY=timeshare

LIBNAME=lservr

OPT=-O0
DEPFLAGS=-MP -MD

CFLAGS=-Wall -Wextra -g $(foreach DEP,$(INCLUDEDIR), -I$(DEP)) $(OPT) $(DEPFLAGS) -$(LIBNAME) -L libs

SOURCECODE=$(foreach SRC, $(LIBSDIR), $(wildcard $(SRC)/*.c))

OBJFILE=$(patsubst %.c, %.o, $(SOURCECODE))
DEPENDENCIES=$(patsubst %.c, %.d, $(SOURCECODE))

all: $(BINARY)

$(BINARY): $(OBJFILE)
	$(CC) -pthread -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -rf $(OBJFILE) $(DEPENDENCIES)

-include $(DEPENDENCIES)

