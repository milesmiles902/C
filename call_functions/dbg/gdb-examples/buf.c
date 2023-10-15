#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA2 "Hello, I'm buf2!"
#define DATA3 "Hello, I'm buf3!"

void
printBufs(long n) {
	char *buf = malloc(n);
	char *buf2 = malloc(8);
	char *buf3 = malloc(8);

	strcpy(buf2, DATA2);
	strcpy(buf3, DATA3);
	gets(buf);

	printf("buf is : '%s'\n", buf);
	printf("buf2 is: '%s'\n", buf2);
	printf("buf3 is: '%s'\n", buf3);
}
