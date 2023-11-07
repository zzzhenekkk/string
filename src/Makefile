# Переменная для цели
TARGET = s21_sprintf
CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11 -g
LFLAGS=#-fsanitize=address

# Имена которые оканчиваются на .c, wildcar - все те файлы, которые удовлятворяют маске
SRC = $(wildcard *.c)
# Имена всех объектных файлов (*.o), так как они не существуют до компиляции, 
#мы подставим из имен с исходным кодом (.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
##############################################

all: clean $(TARGET)
	./$(TARGET)
# то что требуется получить target : то что необходимо чтобы получить то что слева
$(TARGET) : $(OBJ)
	$(CC) $(LFLAGS) $(FLAGS) $(OBJ) -o $(TARGET)


%.o : %.c
	$(CC) $(LFLAGS) $(FLAGS) -c $< -o $@
# $< подставляется то что справа от цели, то есть все обьектные
# $@ подставляется то что стоит в целе

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

style:
	clang-format -n *.c *.h

stylecor:
	clang-format -i *.c *.h

# clang-format -style=Google -i *.c *.h

.PHONY: clean
# PHONY нужна чтобы указать что там не будет файла clean
clean : 
	rm -rf $(TARGET) *.o
	rm -rf CPPLINT.cfg
# удаляем MyProject и все файлы с .o
# Параметр ‘-f‘ в команде rm принудительно удаляет файлы независимо от их прав доступа,
# а также игнорирует несуществующие файлы.
# параметром ‘-r‘ рекурсивно удалит все файлы и подкаталогов в родительской директории.

test : 
	bash grep_test1.sh



# # Так пишутся комментарии 
# # $@ - так подставляется название цели
# ##############################
# # Первый проект c двумя си файлами : main.c my_func.c
# # то что требуется получить target : то что необходимо чтобы получить то что слева
# s21_test : sprintf.o string.o 
# 	gcc sprintf.o string.o -o s21_test 


# # для того чтобы получить main.o
# sprintf.o : sprintf.c
# 	gcc -c sprintf.c -o sprintf.o
# # для того чтобы получить main.o
# string.o : string.c
# 	gcc -c string.c -o string.o

# clean : 
# 	rm s21_test *.o 
# #удаляем MyProject и все файлы с .o
# ##############################










# CC =gcc
# FLAG_C = -c
# FLAG_O = -o
# SANITIZE=-fsanitize=address -g
# CHECK =-lcheck
# MKLIB =ar -rcs
# CFLAGS =-Wall -Werror -Wextra -pedantic -std=c11
# GCOVF =-fprofile-arcs -ftest-coverage
# RMV =rm -rf
# RMVIT =*.o *.a test *.out *.gcda *.gcno *.html *.css tests_s21_string.c

# all: s21_gcov_string.a test gcov_report

# clean:
# 	$(RMV) $(RMVIT)

# test: s21_gcov_string.a tests_s21_string.c
# 	$(CC) $(SANITIZE) $(CFLAGS) $(GCOVF) $(CHECK) $? $(FLAG_O) $@

# tests_s21_string.c:
# 	checkmk tests_s21_string > $@

# s21_gcov_string.a: s21_string.c s21_sprintf.c
# 	$(CC) $(CFLAGS) $(GCOVF) $(FLAG_C) $?
# 	$(MKLIB) $@ *.o
# 	$(RMV) *.o

# s21_string.a: s21_string.c s21_sprintf.c
# 	$(CC) -c $(CFLAGS) $?
# 	$(MKLIB) $@ *.o
# 	$(RMV) *.o

# rebuild: clean all

# gcov_report: test
# 	./$?
# 	gcovr -r . --html --html-details $(FLAG_O) coverage_report.html
# 	$(RMV) tests_s21_string.gcda tests_s21_string.gcno
# 	open coverage_report.html

# linter:
# 	python3 ../materials/linters/cpplint.py *.c *.h