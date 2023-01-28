#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME "socket"

int main(){
  int sock;
  struct sockaddr_un name;
  char buf[BUFSIZ];

  if ((sock = socket(PF_LOCAL, SOCK_DGRAM, 0))) {
    perror("opening datagram socket");
    exit(EXIT_FAILURE);
  }
  
  name.sun_family = PF_LOCAL;
  (void)strncpy(name.sun_path, NAME, sizeof(name.sun_path));
  if (bind(sock, (struct sockaddr *)&name,  sizeof(struct sockaddr_un))) {
    perror("binding name to dattagram socket");
    exit(EXIT_FAILURE);
  }
  if (read(sock, buf, BUFSIZ) < 0)
    perror("readding from socket");
  (void)printf("--. %s\n", buf);
  (void)close(sock);

  (void)unlink(NAME);
  return EXIT_SUCCESS;
}
