LIB_NAME   = decimal.a

SRCS       = decimal_arthm.c \
             decimal_compr.c \
             decimal_convrt.c \
             decimal_other.c \
             decimal_utils.c 

T_NAME     = tests/unit.check
T_SRCS     = tests/check_decimal.c \
             tests/check_decimal_arthm.c \
             tests/check_decimal_compr.c \
             tests/check_decimal_convrt.c \
             tests/check_decimal_other.c \
             tests/check_decimal_utils.c

REPORT_DIR = report
LCOV_INFO  = coverage.info

HEADER     = decimal.h

OBJ_       = $(SRCS:%.c=%.o)

CC         = gcc -std=c11
gcov  : CC = gcc -std=c11 --coverage
debug : CC = gcc -std=c11 -g
vg    : CC = gcc -std=c11 -ggdb3
# CFLAGS     = -I. -Wall -Wextra -Werror
CFLAGS     = -I.
LIBCHECK   = -lcheck

OS = $(shell uname)
ifeq ($(OS), Linux)
	LINUX_LIBS= -lrt -lpthread -lm
#	LINUX_LIBS=-lsubunit -lrt -lpthread -lm
else
	LINUX_LIBS=
endif

.PHONY : all \
         re \
         clean clear \
         cpplint cppcheck leaks vg \
         test gcov_report

# all: cpplint cppcheck $(LIB_NAME)
all: $(LIB_NAME)

re: clean all

gcov: re test

debug: re

gcov_report:
	@make -i gcov
	@lcov -o $(LCOV_INFO) -c -d .
	@genhtml -o $(REPORT_DIR) $(LCOV_INFO)
	@open  $(REPORT_DIR)/index.html

$(LIB_NAME): $(OBJ_) $(HEADER)
	@ar -rcs $(LIB_NAME) $?
	@ranlib $@
	@cp $@ lib$@

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(T_NAME): $(LIB_NAME) $(T_SRCS)
	@$(CC) $(T_SRCS) $(LIBCHECK) -o $(T_NAME) $(LINUX_LIBS) -L. -ldecimal

main: $(LIB_NAME)
	@$(CC) main.c -o main.app -L. -ldecimal
	@./main.app

test: clean $(T_NAME)
	@./$(T_NAME)


leaks: clean $(T_NAME)
	CK_FORK=no leaks --atExit -- ./$(T_NAME)

vg: clean $(T_NAME)
	CK_FORK=no valgrind \
				--leak-check=full  --show-leak-kinds=all \
				--track-origins=yes --verbose \
				--log-file=valgrind.txt ./$(T_NAME)

clean:
	@rm -rf *.o *.a *.gcno */*.gcno *.gcda */*.gcda *.gcov */*.gcov $(T_NAME) coverage** report tests/coverage** tests/*.dSYM valgrind*.*

cpplint:
	@python3 ../materials/linters/cpplint.py  --quiet --extension=c $(SRCS) $(T_SRCS) *.c */*.c

cppcheck:
	@cppcheck -q --enable=all --suppress=missingIncludeSystem $(SRCS) $(T_SRCS) *.c */*.c

doc:
	../materials/build/./run2.sh

miniverter:
	../materials/build/./run3.sh
