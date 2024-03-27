CC=g++
CFLAGS=-Wall

LD=$(CC)
LDFLAGS_EXE=-ldl -lncurses
LDFLAGS_LIB=""

all: point.exe
	@echo "Build done"

point.exe: point.cpp
	@$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS_EXE)
	@echo "(BUILD) $@"

clean:
	@rm -rf *.exe
	@echo "delete complete"