# C compiler
CC = gcc
# Includes
INCLUDES = ../include
# Source files
SOURCES = $(wildcard ../source/*.c)
# Put C settings (-I, -D, etc) here
CFLAGS = -I$(INCLUDES)
# Put compiler settings here
CCFLAGS = -std=c11 -Wall
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
	for runner in $(RUNNERS); do $$runner; done

.PHONY: clean
clean:
	rm -rf */*.o */*.i */*.s */*.gcno */*.gcda */*.gcov $(RUNNERS)
