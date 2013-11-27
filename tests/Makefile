TESTS := $(wildcard *.h)
RUNNER := runner
RUNNER_SRC := runner.cpp
OBJS := $(wildcard $(OBJ_HOME)/*.o)
OBJS_NOMAIN := $(subst $(OBJ_HOME)/main.o,,$(OBJS))

CC := g++
CFLAGS := -Wall -g -std=gnu++11

$(RUNNER): $(RUNNER_SRC) $(OBJS_NOMAIN)
	$(CC) $(CFLAGS) $(RUNNER_SRC) $(OBJS_NOMAIN) -o $(RUNNER) -I$(SRC_HOME)

$(RUNNER_SRC): $(TESTS)
	cxxtestgen --error-printer -o $(RUNNER_SRC) $(TESTS)

.PHONY: run clean
run: $(RUNNER)
	./runner

clean:
	rm -f $(RUNNER)
	rm -f $(RUNNER_SRC)