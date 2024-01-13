/*
 * Demonstrates default standard I/O filedescriptors can close. 
 * To reopen, then you need to explicitly open the terminal and dup(2)
 *
 */

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main() {
  int fd;
  if ((fd = open("/dev/tty", O_WRONLY)) < 0) {
    err(EXIT_FAILURE, "Unable to open /dev/tty");
  }
  (void)printf("Opened /dev/tty on fd#%d.\n", fd);

  (void)printf("Closing_FILENO...\n");
  (void)close(STDERR_FILENO);

  (void)fprintf(stderr, "This message will not be shown.\n");
  if (dup2(fd, STDERR_FILENO) < 0) {
    /* stderr is still closed */
    (void)fprintf(stdout, "Unable to dup2: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  (void)fprintf(stderr, "Error messages back to normal.\n");

  (void)close(fd);
  return EXIT_SUCCESS;
}
