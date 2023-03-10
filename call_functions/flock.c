#include <sys/file.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void progress() {
  for (int i=0; i < 10; i++) {
    (void)write(STDOUT_FILENO, ".", 1);
    sleep(1);
  }
}

int 
main(int argc, char **argv) {
  int i, fd, flags;

  (void)argv;

  if ((fd = open("/tmp/1", O_CREAT|O_RDWR, 0644)) == -1) {
    (void)fprintf(stderr, "Unable to open /tmp/1: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  if (flock(fd, LOCK_SH) < 0) {
    perror("flocking");
    exit(EXIT_FAILURE);
  }

  (void)printf("Shared lock established - sleeping for 10 seconds.\n");  
  progress();
  (void)printf("\nNow trying to get an exclusive lock.\n");

  flags = LOCK_EX;
  if (argc > 1) {
    flags |= LOCK_NB;
  }

  for (i=0; i < 10; i++) {
    if (flock(fd, flags) < 0) {
      (void)printf("Unable to get an exclusive lock.\n");
      if (i==9) {
        (void)printf("Giving up all locks.\n");
        flock(fd, LOCK_UN);
        exit(EXIT_FAILURE);
      }
      sleep(1);
    } else {
        (void)printf("Exclusive lock established.\n");
        break;
    }
    }
    progress();
    (void)printf("\n");
    (void)close(fd);
    exit(EXIT_SUCCESS);
}

