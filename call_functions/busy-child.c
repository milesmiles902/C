#include <sys/wait.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define ARGV0_LENGTH 8 + 1
#define MAXCHILDREN 32

void
work() {
  int i = 0;
  while (1) {
    i++;
  }
}

int
main (int argc, char **argv) {
  int n;
  pid_t pid;

  if (argc == 1) {
    work();
  } else if (argc > 2) {
      (void)fprintf(stderr, "Usage: %s num\n", argv[0]);
      exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);
  if ((n < 1) || (n > MAXCHILDREN)) {
    (void)fprintf(stderr, "Please provide a number > 0 and <= %d.\n", MAXCHILDREN);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < n; i++) {
    if ((pid = fork()) < 0) {
       err(EXIT_FAILURE, "fork");
    } else if (!pid) {
        char argv0[ARGV0_LENGTH];
         bzero(argv0, ARGV0_LENGTH);

      (void)snprintf(argv0, ARGV0_LENGTH, "worker%d", i);

      (void)printf("Created %s: %d\n", argv0, getpid());

      char * const args[] = { argv0, NULL };
      execve("./a.out", args, NULL);
      err(EXIT_FAILURE, "execve");
    }
  }  
  
  while ((pid = wait(NULL)) > 0);
  if ((pid < 0) && errno != ECHILD) {
    err(EXIT_FAILURE, "wait");
  }
  
  return EXIT_SUCCESS;
}
