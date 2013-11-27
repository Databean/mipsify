ALLFILES := $(wildcard src/*)
export OBJ_HOME := $(realpath obj)
export SRC_HOME := $(realpath src)
EXECUTABLE := mipsify
CC := g++

output.s: $(EXECUTABLE) test.c
	./$(EXECUTABLE) test.c output.s

$(EXECUTABLE): $(ALLFILES)
	cd src && $(MAKE)
	${CC} obj/*.o obj/mips32/*.o -o mipsify -std=gnu++11

.PHONY: tests clean
tests: $(EXECUTABLE)
	cd tests && $(MAKE) run

clean:
	rm -f output.s
	rm -f obj/*.o
	rm -f obj/mips32/*.o
	rm -f $(EXECUTABLE)
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
