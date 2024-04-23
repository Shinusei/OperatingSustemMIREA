CC=gcc
CFLAGS=-Wall

LD=$(CC)
LDFLAGS_EXE=-ldl -lncurses
LDFLAGS_LIB=""

all: main.exe
	@echo "Build done"

main.exe: main.c
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_EXE)
	@echo "(BUILD) $@"

clean:
	@rm -rf *.exe
	@echo "delete complete"