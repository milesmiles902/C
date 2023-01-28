#include <sys/param.h>

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
  char  buf[MAXPATHLEN];

  if (argc != 2) {
    fprintf(stderr, "%s: need a directory!\n", argv[0]);
    return(EXIT_FAILURE);
  }
  
  if (chdir(argv[1]) == -1) {
    fprintf(stderr, "%s: unable to chdir to %s\n", argv[0], argv[1]);
    return(EXIT_FAILURE);
  }

  printf("Ok, cwd is now: %s\n", getcwd(buf, MAXPATHLEN));

  exit(EXIT_SUCCESS);
}
