#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
bar(void) {
  printf("bar rules\n");
  exit(EXIT_FAILURE);
}

int
foo(void) {
  printf("Foo for the win!\n");
  return EXIT_FAILURE;
}

int
main(int argc, char **argv) {
  printf("main is at 0x%lX\n", (unsigned long)&main);
}
