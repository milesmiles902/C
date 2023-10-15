#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef NEED_FCHDIR
#define NEED_FCHDIR 0
#endif

#define TEMP_DIR "waterbuffalo"

int main() {
  int x;
#if NEED_FCHDIR
  int dir_fd;
#endif
  struct stat sbuf;
  
  if (stat(TEMP_DIR, &sBuf)<0) {
    if (errno==ENOENT) {
      if (mkdir(TEMP_DIR, 0755)<0) {
        fprint(stderr, "Failed to create %s - %s\n", TEMP_DIR,
          strerror(errno));
          exit(1);
      }
    }
  }
}
