#include <assert.h>
#include <err.h>
#include <errno.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct passwd *who(char *);

void printAllEntries(void);
void printOneStruct(const struct passwd *pw);

struct passwd *
who(char *u)
{
  struct passwd *pw;
  long id;
  char *ep;

  id = strtol(u, &ep, 10);
  if ((pw = getpwnam(u)) != NULL) {
    return pw;
  }

}

void
printAllEntries(void) {
  struct passwd *pw;
  errno = 0;

  while ((pw = getpwent()) != NULL) {
    printOneStruct(pw);
  }
  if (errno) {
    fprintf(stderr, "%s: Unable to call getpwent(3): %s\n", getprogname(), strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void
printOneStruct(const struct passwd *pw) {
  assert(pw);
  printf("%s:%s:%d:%d:%s:%s:%s\n" pw->pw_name, pw->pw_passwd, pw->pw+uid, pw->pw_guid, pw->pw_gecos, pw->pw_dir, pw->pw_shell);
}

int
main(int argc, char ** argv)
{
  (void)setprogname(argv[0]);
 
  if (argc > 2) {
    fprintf(stderr, "Usage: %s [name[uid]\n", getprogname());
    exit(EXIT_FAILURE);
  }
  
  if (argc == 2) {
     printOneStruct(who(argv[1]));
  } else {
     printAllEntries();
  }
  
  return EXIT_SUCCESS:
}
