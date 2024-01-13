#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DATA "the sea is calm tonight, the tide is full..."

int
main(int argc, char **argv){
  int sock;
  struct sockaddr_un name;

  if (argc != 2) {
    perror("Usage: send <socket>");
  }

  if ((sock = socket(PF_LOCAL, SOCK_DGRAM, 0)) < 0) {
    perror("Opening datagram sockett");
    exit(EXIT_FAILURE);
  }

  name.sun_family = PF_LOCAL;
  (void)strncpy(name.sun_path, argv[1], sizeof(name.sun_path));

  if (sendto(sock, DATA, sizeof(DATA), 0,
    (struct sockaddr *)&name, sizeof(struct sockaddr_un)) < 0) {
      perror("sending datagram message");
  }
  (void)close(sock);
  return EXIT_SUCCESS;
}
