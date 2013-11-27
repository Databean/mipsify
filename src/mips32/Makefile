SOURCES := $(wildcard *.cpp)
OBJECTS := $(addprefix $(OBJ_HOME)/mips32/, $(SOURCES:.cpp=.o))
HEADERS := $(wildcard *.h)
PARENT_HEADERS := $(wildcard ../*.h)

CC := g++
CFLAGS := -Wall -c -g -std=gnu++11 -I..

.PHONY: main 
main: $(OBJECTS)
	

$(OBJ_HOME)/mips32/%.o: %.cpp $(HEADERS) $(PARENT_HEADERS)
	$(CC) $(CFLAGS) $< -o $@ -g