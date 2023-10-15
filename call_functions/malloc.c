#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MALLOC_SIZE 1024 * 1024

void
printMalloc(void *p, int s){
  (void)printf("malloc/realloc %d\n", s);
  (void)printf("begins at 0x%12lX\n", (unsigned long)p);
  (void)printf("ends at 0x%12lX\n", (unsigned long)p+s);
  (void)printf("\n");
}

int
main() {
  void *ptr;

  if ((ptr = malloc(BUFSIZ)) == NULL) {
    err(EXIT_FAILURE, "malloc");
  }
  printMalloc(ptr, BUFSIZ);

  if ((ptr = realloc(ptr, BUFSIZ / 2)) == NULL) {
    err(EXIT_FAILURE, "realloc");
  }
  printMalloc(ptr, BUFSIZ / 2);
  
  if ((ptr = realloc(ptr, MALLOC_SIZE)) == NULL) {
    err(EXIT_FAILURE, "realloc");
  }
  printMalloc(ptr, MALLOC_SIZE);

  if ((ptr = realloc(ptr, BUFSIZ *2)) == NULL) {
    err(EXIT_FAILURE, "realloc");
  }
  printMalloc(ptr, BUFSIZ *4);

  return EXIT_SUCCESS;
}
