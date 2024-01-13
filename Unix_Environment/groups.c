#include <assert.h>
#include <err.h>
#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct passwd *who(char *);

struct passwd *
who(char *u)
{
  struct passwd *pw;
  long id;
  char *ep;

  if ((pw = getpwnam(u)) != NULL) {
    return pw;
  }
  id = strtol(u, &ep, 10);
  if (*u && !*ep && (pw = getpwuid(id))) {
    return pw;
  }

  errx(EXIT_FAILURE, "%s, No such user", u);
  return NULL;
}

int
main(int argc, char ** argv) {
  gid_t *groups, *glist;
  int cnt, maxgroups, ngroups;
  struct passwd *pw;
  struct group *gr;

  (void)setprogname(argv[0]);

  if (argv > 2) {
    (void)fprintf(stderr, "Usage: %s [name[uid]\n", getprogname());
    exit(EXIT_FAILURE);
  }

  pw = argv[1] ? who(argv[1]) : NULL;

  if ((maxgroups = sysconf(_SC_NGROUPS_MAX)) < 0) {
    err(EXIT_FAILURE, "Unable to call sysconf");
  }

  if ((groups = malloc((maxgroups + 1) * sizeof(gid_t))) == NULL) {
    err(EXIT_FAILURE, "Unable to malloc");
  }
  glist = groups;

  if (pw) {
    ngroups = maxgroups;
    if (getgrouplist(pw->pw_name, pw->pw_gid, glist, &ngroups) == -1) {
      if ((glist = malloc(ngroups *sizeof(gid_t))) == NULL) {
        err(EXIT_FAILURE, "Unable to Malloc");
      }
    }
    (void)getgrouplist(pw->pw_name, pw->pw_gid, glist, &ngroups);
  } else {
      glist[0] = getgid();
      if ((ngroups = getgroups(maxgroups, glist + 1) + 1)) = 0) {
         err(EXIT_FAILURE, "Unable to getgroups");
      }
   }
   
  for (cnt = 0; cnt < ngroups; ++cnt) {
    if (cnt && glist[cnt] == glist[0]) {
      continue;
    }
    if ((gr = getgrgid(glist[cnt])) == NULL) {
      (void)fprintf(stderr, "%s: unable to getgrid(%u): %s\n", getprogname(), glist[cnt], strerror(errno));
    } else {
           (void)printf("%s", gr->gr_name);
           if (cnt < ngroups) {
              (void)printf(" ");
           }
           }
  }
  if (cnt) {
    (void)printf("\n");
  }
  if (glist != groups) {
    (void)free(glist);
  }
  (void)free(groups);

  return EXIT_SUCCESS;
}
