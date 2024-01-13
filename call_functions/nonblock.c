#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024000

int main(int argc, char **argv) {
  int flags, count, loops, num;
  char buf[BUFSIZE], *ptr;

  (void)argv;

  memset(buf, 'a', BUFSIZE);

  if ((flags = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) {
    perror("getting file flags");
    exit(EXIT_FAILURE);
  }

  if (argc > 1) {
    if (fcntl(STDOUT_FILENO, F_SETFL, flags|0_NONBLOCK) < 0) {
      perror("setting file flags");
      exit(EXIT_FAILURE);
    }
  }

  for (loops = 0; loops < 50; loops++) {
    ptr = buf;
    num = BUFSIZE;
    while (num > 0) {
      count = write(STDOUT_FILENO, ptr, num);
      if (count >= 0) {
        ptr += count;
        num -= count;
        (void)fprintf(stderr, "wrote %d bytes\n", count);
      } else {
        (void)fprintf(stderr, "write error: %s\n",
                           strerror(errno));
      }
    }
  }
}
