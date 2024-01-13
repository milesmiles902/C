
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DATA1 "In Xanadu, did Kubla Khan..."
#define DATA2 "A stately pleasure dome decree..."

int main() {
  int sockets[2], child;
  char buf[BUFSIZ];

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) {
    perror("opening stream socket pair");
    exit(1);
  }

  if ((child = fork()) == -1)
    perror("fork");
  else if (child) {
    close(sockets[0]);
    printf("Parent (%d) --> sending: %s\n", getpid(), DATA1);
    if (write(sockets[1], DATA1, sizeof(DATA1)) < 0)
      perror("writing stream message");
    if (read(sockets[1], buf, BUFSIZ) < 0)
      perror("reading stream message");
    printf("Parent (%d) --> reading: %s\n", getpid(), buf);
    close(sockets[1]);
  } else {
      close(sockets[1]);
      printf("Child (%d) --> sending: %s\n", getpid(), DATA2);
      if (write(sockets[0], DATA2, sizeof(DATA2)) < 0)
        perror("writing stream message");
      if (read(sockets[0], buf, BUFSIZ) < 0)
        perror("reading stream message");
      printf("Child (%d) --> reading: %s\n", getpid(), buf);
      close(sockets[0]);
    }
    return 0;
}
