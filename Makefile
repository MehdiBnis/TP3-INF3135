# Makefile totalement repris de mon TP2

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

EXEC = recherche
CSS = ./misc/github-pandoc.css
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

LDFLAGS = -lcunit
TEST_EXEC = test_recherche
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(patsubst tests/%.c,tests/obj/%.o,$(TEST_SRC))

.PHONY: all clean html test

all: link

link: compile

# JEU

compile: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@


obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) -o $@ -c $< $(CFLAGS)

# TESTS

test: all cunit-test test-clean

cunit-test: compile-cunit launch-cunit

compile-cunit: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ) $(filter-out obj/main.o,$(OBJ))
	$(CC) $^ -o $@ $(LDFLAGS)

tests/obj/%.o: tests/%.c
	@mkdir -p tests/obj
	$(CC) -o $@ -c $< $(CFLAGS)

launch-cunit:
	./$(TEST_EXEC)

html:
	pandoc -o README.html -sc $(CSS) README.md

clean: obj-clean test-clean html-clean

obj-clean:
	rm -rf obj
	rm -rf $(EXEC)

test-clean:
	rm -rf tests/obj
	rm -rf obj
	rm -f $(TEST_EXEC)
	rm -rf $(EXEC)

html-clean:
	rm -f *.html
