#include <sys/resource.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv) {
  int n, p1, p2;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s num\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  n = atoi(argv[1]);

  errno = 0;
  if ((p1 = getpriority(PRIO_PROCESS, getpid())) == -1) {
    if (errno != 0) {
      err(EXIT_FAILURE, "getpriority");
    }
  }
  (void)printf("My current priority is: %d\n", p1);

  if (setpriority(PRIO_PROCESS, getpid(), n) == -1) {
    err(EXIT_FAILURE, "setpriority");
  }

  errno = 0;
  if ((p2 = getpriority(PRIO_PROCESS, getpid())) == -1) {
    if (errno != 0) {
      err(EXIT_FAILURE, "getpriority");
    }
  }
  (void)printf("My new priority is: %d\n", p2);

  
  if (setpriority(PRIO_PROCESS, getpid(), n) == -1) {
    err(EXIT_FAILURE, "setpriority");
  }
  
  if (setpriority(PRIO_PROCESS, getpid(), n) == -1) {
    if (errno != 0) {
      err(EXIT_FAILURE, "getpriority");
    }
  }

  if ((p2 = getpriority(PRIO_PROCESS, getpid())) == -1) {
    if (errno != 0) {
      err(EXIT_FAILURE, "getpriority");
    }
  }

  (void)printf("My priority %sis: %d\n", (p1 != p2) ? "still " : "", p2);
  return 0;
}
