#include <sys/wait.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main() {
  (void)printf("Let's create some zombies!\n");

  for (int i = 0; i < 5; i++) {
    pid_t pid;
   
    if ((pid = fork()) < 0) {
      err(EXIT_FAILURE, "fork error");
    }
    
    if (pid == 0) {
      exit(EXIT_SUCCESS);
    } else {
        (void)printf("===\n");
        system("ps a | grep'[^ ]'a.ou[t]");
        sleep(1);
    }
  }
  (void)printf("I'm going to sleep - try to kill my zombie children. if you like.\n");
  sleep(30);
  (void)printf("That's enough zombies. Let's have init clean them up.\n");
  (void)printf("Remember to run 'ps a | grep a.ou[t]' to verify.\n");
  return EXIT_SUCCESS;
}
