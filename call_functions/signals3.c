#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef SLEEP
#define SLEEP 3
#endif

int s = 0;

static void
sig_quit(int signo) {
  (void)signo;
  (void)printf("In sig_quit, s=%d. Now sleeping...\n", ++s);

  (void)sleep(SLEEP);

  (void)printf("sig_quit, s=%d: exiting\n", s);
}

static void
sig_int(int signo) {
  (void)signo;
  (void)printf("Now in sig_int, s=%d. Returning immediately.\n", ++s);
}

int
main(int argc, char **argv) {
  sigset_t newmask, oldmask, pendmask;
  int ismember = 0;

  (void)argv;
  (void)printf("\n=> Establishing initial signal hander via signal(3).\n");
  if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
    err(EXIT_FAILURE, "unable to set SIGQUIT signal handler");
  }

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    err(EXIT_FAILURE, "unable to set SIGINT signal handler");
  }

  if (sigemptyset(&newmask) < 0) {
    err(EXIT_FAILURE, "sigemptyset");
  }

  if (sigaddset(&newmask, SIGQUIT) < 0) {
    err(EXIT_FAILURE, "sigaddset");
  }
  
  (void)printf("\n=> Blocking delivery of SIGQUI...\n");
  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
    err(EXIT_FAILURE, "unable to block SIGQUIT");
  }
  
  (void)printf("\n=> Now going to sleep for %d seconds...\n", SLEEP);
  (void)sleep(SLEEP);

  if (argc > 1) {
    if(signal(SIGQUIT, SIG_IGN) == SIG_ERR) {
      err(EXIT_FAILURE, "Unable to ignore SIGQUIT");
    }
  }

  printf("\n=> Checking if any signals are pending...\n");
  if (sigpending(&pendmask) < 0) {
    err(EXIT_FAILURE, "sigpending");
  }
  
  if ((ismember = sigismember(&pendmask, SIGQUIT)) < 0) {
    err(EXIT_FAILURE, "sigismember");
  }
  
  if (ismember) {
    (void)printf("Pending SIGQUIT found .\n");
  }

  (void)printf("\n=> Unblocking SIGQUIT...\n");
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
    err(EXIT_FAILURE, "unable to unblock SIGQUIT");
  }

  (void)printf("SIGQUIT unblocked - sleeping some more ...\n");

  (void)sleep(SLEEP);

  (void)printf("Now exiting.\n");
  exit(EXIT_SUCCESS);
}
