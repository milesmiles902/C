#include <sys/wait.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 32

void
readData(int fd) {
  int n;
  char buf[NUM];
  off_t offset;

  if ((offset = lseek(fd, 0, SEEK_CUR)) < 0) {
    err(EXIT_FAILURE, "%d lseek error", getpid());
  }
  
  (void)printf("%d offset is now: %d\n", getpid(), offset);
  if ((n = read(fd, buf, NUM)) < 0) {
    err(EXIT_FAILURE, "PID %d: read error", getpid());
  }
}

int 
main(int argc, char **argv){
  int fd;
  pid_t pid;

  if(argc != 2) {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    err(EXIT_FAILURE, "open error");
  }
  
  (void)printf("Starting pid is: %d\n", getpid());

  readData(fd);

  if ((pid = fork()) < 0) {
    err(EXIT_FAILURE, "fork error");
  } else if (pid == 0) {
      if (lseek(fd, NUM, SEEK_CUR) < 0) {
        err(EXIT_FAILURE, "child lseek error");
      }
      (void)printf("child %d done seeking\n", getpid());
      sleep(2);
      readData(fd);
      } else {
          sleep(1);
          readData(fd);
      }
      
      (void)wait(NULL);
      (void)close(fd);
      return EXIT_SUCCESS;
}    
