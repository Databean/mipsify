SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix $(OBJ_HOME)/, $(SOURCES:.cpp=.o))
HEADERS := $(wildcard *.h)

CC := g++
CFLAGS := -Wall -c -g -std=gnu++11 -I. -I$(INCL_HOME)

.PHONY: main 
main: $(OBJECTS) $(OBJ_HOME)/lex.yy.o $(OBJ_HOME)/y.tab.o
	cd mips32 && $(MAKE)

$(OBJ_HOME)/%.o: %.cpp $(HEADERS) lex.yy.c y.tab.c
	$(CC) $(CFLAGS) $< -o $@ -g

lex.yy.c: scanner.l y.tab.c $(HEADERS)
	flex scanner.l
	

y.tab.c: parser.y $(HEADERS)
	bison -dvty parser.y

$(OBJ_HOME)/lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) $< -o $@ -g

$(OBJ_HOME)/y.tab.o: y.tab.c
	$(CC) $(CFLAGS) $< -o $@ -g

.PHONY: clean
clean:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f lex.yy.c
	rm -f y.output
