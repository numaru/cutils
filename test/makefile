# C compiler
CC = gcc
# Includes
INCLUDES = ../include
# Source files
SOURCES = $(wildcard ../source/*.c)
# Put C settings (-I, -D, etc) here
CFLAGS = -I$(INCLUDES)
# Put compiler settings here
CCFLAGS = -std=c11 -Wall -g
CCFLAGS += -ftest-coverage -fprofile-arcs -O0
# Put linker settings here
LDFLAGS = -lgcov -coverage
# Test targets
TESTS = $(dir $(wildcard */main.c))
# Runners
RUNNERS = $(addsuffix runner, $(TESTS))

.PHONY: all
all: $(RUNNERS)

.SECONDEXPANSION:
$(RUNNERS): $(SOURCES) $$(addsuffix main.c, $$(dir $$@))
	cd $(dir $@) && $(CC) -o ../$@ -I../$(INCLUDES) $(CCFLAGS) $(LDFLAGS) $(addprefix ../, $^) && cd ..

.PHONY: test
test: $(RUNNERS)
	error=0; for runner in $(RUNNERS); do if ! $$runner; then error=1; fi; done; exit $$error

.PHONY: clean
clean:
	rm -rf */*.o */*.i */*.s */*.gcno */*.gcda */*.gcov $(RUNNERS)
