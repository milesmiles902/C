/* The Fibonacci sequence is defined such that each number
 * is the sum of the two preceding ones. */

#include <stdio.h>
#include <stdlib.h>

int fib(int i) {
	int n;
	while (i > 0) {
		n = fib(i-2) + fib(i-1);
	}

	return n;
}

int
main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: %s num\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", fib(atoi(argv[1])));
	exit(EXIT_SUCCESS);
}
