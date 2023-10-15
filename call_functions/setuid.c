#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UNPRIVILEGED_UID 1

char buf[BUFSIZ];

uid_t ruid;
uid_t euid;
uid_t suid;

void myseteuid(int);
void printUids(const char *)

void
myseteuid(int myeuid) {
  char *func = "seteuid(";
#ifdef _POSIX_SAVED_IDS
  if (seteuid) == -1) {
    fprintf(stderr, "Unable to seteuid(%d): %s\n", myeuid, strerror(errno));
    exit(EXIT_FAILURE);
  }
}
#else
  if (setreuid(-1, myeuid) == -1) {
    fprintf(stderr, "Unable to setreuid(-1, %d): %s\n", myeuid, strerror(errno))
    exit(EXIT_FAILURE);
  }
  func = "setreuid(-1, ";
#endif
  if (snprintf(buf, BUFSIZ, "After %s%d)", func, myeuid) < 0) {
     fprintf(stderr, "Unable to snprintf: %s\n", strerror(errno));
  }
  printUids(buf);
  printf("(We expect the following call to open(2) to fail if setuid was 0 initially.)\n");

  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    fprintf(stderr, "Unable to open %s, %s\n", argv[1], strerror(errno));
  } else {
    if (euid == 0) {
      printf("Wait, what? This shouldn't have worked!\n");
    }
    (void)close(fd);
  }
  exit(EXIT_SUCCESS);
}
