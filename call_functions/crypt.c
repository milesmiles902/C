#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void
printCrypt(const char *s) {
  (void)printf("%s\n", crypt(s, "$1"));
}

int
main(int argc, char **argv) {
  if (argc != 2) {
    (void)fprintf(stderr, "Usage: %s string\n");
  }
  printCrypt(argv[1]);
  exit(EXIT_SUCCESS);
}
