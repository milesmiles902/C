#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FRED 1001
#define USERS_GID 100
#define TTY_GID 4

void
mychown(const char *file, int uid, int gid) {
  if (chown(file, uid, gid) < 0) {
    fprintf(stderr, "Unable to chown(%s, %d, %d); %s\n", file, uid, gid, strerror(errno));
  } else {
    printf("Succesfully chowned %s %d:%d.\n", file, uid, gid);
  }
}

int
main(int argc, char **argv) {
  if (argc !=2) {
     fprintf(stderr, "Usage: %s file\n", argv[0]);
     exit(EXIT_FAILURE);
  }

  mychown(argv[1], getuid(), -1);

  mychown(argv[1], getuid(), -1);

  mychown(argv[1], -1, USERS_GID);

  mychown(argv[1], -1, TTY_GID);

  exit(EXIT_SUCCESS);
}
