OUTDIR = $(shell cd ../build && pwd)
UNAME = $(shell uname -s)
CC = gcc -Wall -Werror -Wextra -std=c11
SOURCES_LIB = action_matrix_forverter.o create_forverter.o mathematics_matrix_forverter.o
SOURCES_TEST = action_matrix.o create.o mathematics_matrix.o
OUTNAME = "tests"


ifeq ($(UNAME),Darwin)
	FLAGSS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGSS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif


all: clean build clean

build: style s21_matrix.a test gcov_report

rebuild: all

gcov_report:
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html

test: s21_tests.c $(SOURCES_TEST)
	$(CC) s21_tests.c $(SOURCES_TEST) $(FLAGSS) -o $(OUTNAME)
	./$(OUTNAME)

s21_matrix.a: $(SOURCES_LIB) s21_matrix.h
	ar -rcs s21_matrix.a $(SOURCES_LIB) s21_matrix.h
	ranlib s21_matrix.a



### OBJECT FILES

create.o: mainMatrix/create.c
	$(CC) -c --coverage mainMatrix/create.c -o create.o

action_matrix.o: mainMatrix/action_matrix.c
	$(CC) -c --coverage mainMatrix/action_matrix.c -o action_matrix.o

mathematics_matrix.o: mainMatrix/mathematics_matrix.c
	$(CC) -c --coverage mainMatrix/mathematics_matrix.c -o mathematics_matrix.o


create_forverter.o: mainMatrix/create.c
	$(CC) -c mainMatrix/create.c -o create_forverter.o

action_matrix_forverter.o: mainMatrix/action_matrix.c
	$(CC) -c mainMatrix/action_matrix.c -o action_matrix_forverter.o

mathematics_matrix_forverter.o: mainMatrix/mathematics_matrix.c
	$(CC) -c mainMatrix/mathematics_matrix.c -o mathematics_matrix_forverter.o

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n mainMatrix/*.c

valgrind:
	valgrind ./$(OUTNAME) 

clean:
	rm -rf *.o *.a *.so coverage* *.gcno *.gcda *.gcov *.dSYM *.cfg *.py a.out ".clang-format" $(OUTNAME) 

