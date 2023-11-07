CC =gcc
FLAG_C = -c
FLAG_O = -o
SANITIZE=-fsanitize=address -g
CHECK =-lcheck
MKLIB =ar -rcs
CFLAGS =-Wall -Werror -Wextra -pedantic -std=c11
GCOVF =-fprofile-arcs -ftest-coverage
RMV =rm -rf
RMVIT =*.o *.a test *.out *.gcda *.gcno *.html *.css tests_s21_string.c

all: s21_gcov_string.a test gcov_report

clean:
	$(RMV) $(RMVIT)

test: s21_gcov_string.a tests_s21_string.c
	$(CC) $(SANITIZE) $(CFLAGS) $(GCOVF) $(CHECK) $? $(FLAG_O) $@

tests_s21_string.c:
	checkmk tests_s21_string > $@

s21_gcov_string.a: s21_string.c s21_sprintf.c
	$(CC) $(CFLAGS) $(GCOVF) $(FLAG_C) $?
	$(MKLIB) $@ *.o
	$(RMV) *.o

s21_string.a: s21_string.c s21_sprintf.c
	$(CC) -c $(CFLAGS) $?
	$(MKLIB) $@ *.o
	$(RMV) *.o

rebuild: clean all

gcov_report: test
	./$?
	gcovr -r . --html --html-details $(FLAG_O) coverage_report.html
	$(RMV) tests_s21_string.gcda tests_s21_string.gcno
	open coverage_report.html

linter:
	python3 ../materials/linters/cpplint.py *.c *.h
