#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#define INTERVALS 3

int
main() {
  double loadavg[INTERVALS];

  if (getloadavg(loadavg, INTERVALS) == -1) {
    err(EXIT_FAILURE, "getloadavg");
  }

  (void)printf("%lf %lf %lf\n", loadavg[0], loadavg[1], loadavg[2]);
  return EXIT_SUCCESS;
}
