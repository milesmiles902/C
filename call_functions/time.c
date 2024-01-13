#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main() {
  time_t t;
  
  if ((t = time(NULL)) < 0) {
    err(EXIT_FAILURE, "unable to call time()");
  }
  
  printf("time(3) says: %ld\n", t);

  return EXIT_SUCCESS;
}
