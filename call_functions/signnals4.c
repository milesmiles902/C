#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef SLEEP
#define SLEEP 5
#endif

#define MSG "SIGQUIT caught.\n"

static void
sig_quit(int signo){
  (void)signo;
  (void)write(STDOUT_FILENO, MSG, strlen(MSG));
}

int
main(int argc, char **argv) {
  (void)argc;

  if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
    err(EXIT_FAILURE, "unable to set SIGQUIT signal handler");
  }

  (void)printf("=> Waiting for a signal...");
  if (argc > 1) {
    pause();
  }
  
  (void)printf(" done.\n");
  exit(EXIT_SUCCESS);
}
