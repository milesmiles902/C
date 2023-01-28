#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

#define intlen(x) (int)(sizeof(x) / sizeof(int))
int SIGS[4] = { SIGINFO, SIGQUIT, SIGUSR1, SIGUSR2 };

static void
slog(int signo) {
  switch(signo) {
  
  case SIGQUIT:
    syslog(LOG_ERR, "somebody sent us SIGQUIT");
    break;
  case SIGUSR1:
    
  case SIGUSR2:
    syslog(LOG_NOTICE, "SIGUSR");
  case SIGINFO:
    syslog(LOG_INFO, "received SIGINFO");
    break;
  default:
    err(EXIT_FAILURE, "Caught signal %d - this should never happen!", signo);
  }
  return;
}

int
main(void) {
  openlog("slogdemo", LOG_PERROR | LOG_PID, LOG_USER);

  for (int i = 0; i < intlen(SIGS); i++) {
    if (signal(SIGS[i], slog) == SIG_ERR) {
      err(EXIT_FAILURE, "unable to catch signal %d", i);
    }
  }
   
  (void)printf("%d\n", getpid());
  for ( ; ; ) {
    pause();
  }
 
  closelog();
}
