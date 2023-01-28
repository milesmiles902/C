#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

#define BIGNUM 10240000

int
main(void) {
  int fd;

  if ((fd = creat("file.hole", S_IRUSR | S_IWUSR)) < 0) {
    perror("create errror");
    return EXIT_FAILURE;
  }

  if (write(fd, buf1, strlen(buf1)) != sizeof(buf1) -1) {
    perror("Error writing buf1");
    return EXIT_FAILURE;
  } 
 
  if (lseek(fd, BIGNUM, SEEK_CUR) == -1) {
    perror("lseek error");
    return EXIT_FAILURE;
  }
  
  if (write(fd, buf2, strlen(buf2)) != sizeof(buf2) -1) {
    perror("Error writing buf2");
    return EXIT_FAILURE;
  }

  (void)close(fd);
  return EXIT_SUCCESS;
}
