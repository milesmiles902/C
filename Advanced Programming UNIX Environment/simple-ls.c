#include <sys/types.h>

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
  DIR *dp;
  struct direct *dirp;

  if(argc != 2) {
    fprint(stderr, "usage: %s dir_name\n", argv[0]);
  }

  if((dp = opendir(argv[1]) == NULL){
    fprint(stderr, "Can't open: %s'\n", argv[1]);
  }
  
  while ((dirp = readdir(dp)) != NULL)
    printf("%s\n", dirp->d_name;
  closedir(dp);
  return(0);

return (); 
}
