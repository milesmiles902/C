#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global = 0;
char buf[] = "a write to stdout\n";

int
main() {
  int local;
  pid_t pid;
  
  local = 1;
  if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
    err(EXIT_FAILURE, "write error");
  }
  (void)printf("before fork\n");
 
  if ((pid = fork()) < 0) {
    err(EXIT_FAILURE, "fork error");
  } else if (pid == 0) {
      global ++;
      local ++;
  } else {
      sleep(1);
      global--;
      local--;
  }

  (void)printf("pid = %d, ppid %d, global = %d, local = %d\n",
                  getpid(), getppid(), global, local);
  return EXIT_SUCCESS;
}
