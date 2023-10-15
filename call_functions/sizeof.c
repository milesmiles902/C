#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA "1234567890"

struct struct1 {
  char *s;
};

struct struct2 {
  char *s;
  int i;
};

struct struct3 {
  char *s;
  int i;
  int j;
};

struct struct4 {
  struct struct1 s1;
  struct struct2 s2;
  struct struct3 s3;
};

struct flex {
  char c;
  char array[];
};

int main() {
  
  printf("Base data types:\n");
  printf("sizeof(int)         : %4lu\n", sizeof(int));
  printf("sizeof(float)       : %4lu\n", sizeof(float));
  printf("sizeof(double)      : %4lu\n", sizeof(double));
  printf("sizeof(char)        : %4lu\n", sizeof(char));

  printf("\nPointers:\n");
  printf("sizeof(int *)       : %4lu\n", sizeof(int *));
  printf("sizeof(void *)      : %4lu\n", sizeof(void *));
  printf("sizeof(char *)      : %4lu\n", sizeof(char *));

  printf("\nStructs:\n");
  printf("sizeof(struct struct1): %4lu\n", sizeof(struct1)); 
  printf("sizeof(struct struct2): %4lu\n", sizeof(struct2));
  printf("sizeof(struct struct3): %4lu\n", sizeof(struct3));
  printf("sizeof(struct struct4): %4lu\n", sizeof(struct4));

  printf("\nFlex struct:\n");
  printf("sizeof(struct flex)   : %4lu\n", sizeof(struct flex));

  struct flex f1;
  struct flex f2;

  strncpy(f2.array, "flex", 32);

  printf("sizeof(f1)            : %4lu\n", sizeof(f1));
  printf("sizeof(f2)            : %4lu\n", sizeof(f2));

  /* Segfault:
  strncpy(f3->array, "flex", 32);
  */

  printf("\nStrings:\n");
  
  printf("Macro string: '#define DATA \"%s\"'\n", DATA);
  printf("sizeof(DATA)          : %4lu (strlen: %4lu\n", sizeof(DATA), strlen(DATA));
  
  char buf1[] = "abc";
  printf("\nInitialized buffer: 'buf1[] = \"abc\"'\n");
  printf("sizeof(buf1)          : %4lu (strlen: %4lu)\n", sizeof(buf1), strlen(buf1));

  char buf2[BUFSIZ];
  printf("\nFixed buffer, size known at compile time: \"buf2[%3]\"\n", BUFSIZ);
  printf("sizeof(buf3)          : %4lu (strlen: %4li)\n", sizeof(buf2), strlen(buf2));

  char buf3[BUFSIZ] = { 'a', 'b', 'c' };
  printf("\nFixed size, initialized buffer: \"buf3[%d] = { 'a', 'b', 'c'}\"\n", BUFSIZ);
  printf("sizeof(buf3)          : %4lu (strlen: %4lu)\n", sizeof(buf3), strlen(buf3)); 
  
  char *s1 = "abc";
  printf("\nInitialized pointer: 'char *s1 = \"abc\"'\n");
  printf("sizeof(s1)            : %4lu (strlen: %4lu)\n", sizeof(s1), strlen(s1));

  char *s2 = buf3;
  printf("\nInitialized pointer: 'char *is ikli2 = buf3'\n");
  printf("sizeof(s2)            : %4lu (strlen: %4lu)\n", sizeof(s2), strlen(s2));

  char *s3;
  if ((s3 = malloc(BUFSIZ)) == NULL) {
    fprintf(stderr, "Unable to allocate memory: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  printf("\nA pointer to malloc(%d)'d memory:\n", BUFSIZ);
  printf("sizeof(s3)             : %4lu (strlen, %4lu)\n", sizeof(s3), strlen(s3));

  (void)strncat(s3, "0123456789", BUFSIZ);
  printf("\nAfter strncat(3)ing \"0123456789\" to 's3':\n");
  printf("sizeof(s3)             : %4lu (strlen: %4lu)\n", sizeof(s3), strlen(s3));


  return EXIT_SUCCESS;
}
