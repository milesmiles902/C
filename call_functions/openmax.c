#include <sys/resource.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
openFiles(int num) {
  struct stat stats;
  int count = 0;
  int fd;

  for (int i = 0; i < num; i++) {
    if (fstat(i, &stats) == 0) {
      printf("Fd #%d is open.\n", i);
      count++;
    }
  }
  printf("Currently open files: %d\n", count);

  for (int i = count; i <= num + 1; i++) {
    if ((fd = open("/dev/null", O_RDONLY)) < 0) { 
      if (errno == EMFILE) {
        printf("Opened %d additional files, then failed: %s (%d)\n", i - count, strerror(errno), errno);
        break;
    } else {
         fprintf(stderr, "Unable to open '/dev/null' on fd#%d: %s (errno %d)\n", i, strerror(errno), errno);
         break;
       }
     }
  }
} 

int
main() {
  int openmax;
  struct rlimit  rlp;

#ifdef OPEN_MAX
  printf("OPEN_MAX is defined as %d.\n", OPEN_MAX);
#else
  printf("OPEN_MAX is not defined on this platform.\n");
#endif
  printf("'getconf OPEN_MAX' says: ");
  (void)fflush(stdout);
  (void)system("getconf OPEN_MAX");

  errno = 0;
  if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
    if (errno == 0) {
      fprintf(stderr, "sysconf(3) considers _SC_OPEN_MAX unsorrpored?\n");
    } else {
        fprintf(stderr, "sysconf(3) error for _SC_OPEN_MAX: %s\n");
    }
    exit(EXIT_FAILURE);
  }
  openmax = (int)rlp.rlim_cur;
  printf("getrlimit(2) says this process can open %d files.\n", openmax);

  printf("Which one is it?\n\n");

  openFiles(openmax);

  return EXIT_SUCCESS;
}
