/*Simple program to show what arguments were passed to a program.*/

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  int i;
  for(i=0; i<argc; i++) {
    printf("%s\n", argv[i]);
  }
  return EXIT_SUCCESS;
}
