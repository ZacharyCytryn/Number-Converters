CPU := $(shell uname -p)
ifeq ($(CPU),arm)
export LD_LIBRARY_PATH=/opt/homebrew/lib/:$LD_LIBRARY_PATH
INCD = -I /opt/homebrew/include/
LIBD = -L /opt/homebrew/lib/
endif

CFLAGS = -g -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -DDEBUG
EXTRA_CFLAGS = -pedantic
TEST_RESULTS := "part2_results.json"
OCLINT_REPORT := "oclint_report.html"

all: integers tests

integers: integers.o
	gcc -o integers integers.o
	 
integers.o: integers.c
	gcc $(CFLAGS) ${EXTRA_CFLAGS} ${INCD} -c integers.c

tests: tests.o 
	gcc -lcriterion ${LIBD} -o tests tests.o 

tests.o: tests.c
	gcc $(CFLAGS) ${EXTRA_CFLAGS} ${INCD} -c tests.c

test:
	./tests -j1 --verbose --json=$(TEST_RESULTS)

clean:
	rm -fr integers tests *.o tests.out $(TEST_RESULTS) $(OCLINT_REPORT)

.PHONY: all test

