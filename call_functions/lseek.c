#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void) {
  if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1 )
    printf("Cannot seek\n");
  else
    printf("Seek OK\n");
  return EXIT_SUCCESS;
}
