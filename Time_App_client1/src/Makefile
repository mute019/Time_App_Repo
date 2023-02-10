CC=gcc
INCLUDEDIR=. .. ../includes
LIBSDIR= . .. ../libs
BINARY=../build/client

OPT=-O0
DEPFLAGS=-MP -MD

CFLAGS=-Wall -Wextra -g $(foreach DEP,$(INCLUDEDIR), -I$(DEP)) $(OPT) $(DEPFLAGS)

SOURCECODE=$(foreach SRC, $(LIBSDIR), $(wildcard $(SRC)/*.c))

OBJFILE=$(patsubst %.c, %.o, $(SOURCECODE))
DEPENDENCIES=$(patsubst %.c, %.d, $(SOURCECODE))

all: $(BINARY)

$(BINARY): $(OBJFILE)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJFILE) $(DEPENDENCIES)

-include $(DEPENDENCIES)

