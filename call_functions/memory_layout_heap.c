#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ARRAY_SIZE 16
#define MALLOC_SIZE 32

#define MSD "I'm a constant!"

char array[ARRAY_SIZE];
char *string = "a string";
char *string2;
int num = 10;
int num2;

extern char **environ;

void func(void);
void func2(const char *);

int 
main(int argc, char **argv){
  int var;
  char *ptr;

  char func_array[ARRAY_SIZE];

  (void)printf("High address (args and env):\n");
  (void)printf("----------------------------\n");
  (void)printf("environ[0] at                                         : 0x%12ln\n", (unsigned long)environ);
  (void)printf("last arg at                                           : 0x%12ln\n", (unsigned long)&argv[argc]);
  (void)printf("first arg at                                          : 0x%12lx\n", (unsigned long)&argv[0]);
  (void)printf("\n");

  (void)printf("Stack:\n");
  (void)printf("------\n");
  (void)printf("First variable inside main at                         : 0x12lX\n", (unsigned long)&var);
  (void)printf("func_array[] ends at                                  : 0x%12lX\n", (unsigned long)&func_array[ARRAY_SIZE]);
  (void)printf("func_array[] (like 'array[]', but on stack) begins at : 0x%12lX\n", (unsigned long)&func_array[0]);

  (void)printf("argc at                                               : 0x%12lX\n", (unsigned long)&argc);
  (void)printf("argv at                                               : 0x%12lX\n", (unsigned long)&argv);
  
  func2("from  main");
  func();
  
  (void)printf("\n"); 

  (void)printf("Heap:\n");
  (void)printf("----\n");
  if ((ptr = malloc(MALLOC_SIZE)) == NULL) {
    err(EXIT_FAILURE, "Unable to allocate memory");
  }

  (void)printf("malloced area ends at                                 : 0x%12lX\n", (unsigned long)ptr+MALLOC_SIZE);
  (void)printf("malloced area begins at                               : 0x%12lX\n", (unsigned long)ptr);
  free(ptr);
  (void)printf("\n");
  
  (void)printf("Uninitialized Data (BSS):\n"); 
  (void)printf("-------------------------\n");
  (void)printf("array[] ends at                                       : 0x%12lX\n", (unsigned long)&array[ARRAY_SIZE]);
  (void)printf("array[] (uninitialized, fixed-size char * on BSS) from: 0x%12lX\n", (unsigned long)&array[0]);
  (void)printf("num2 (uninitialized global int) at                    : 0x%12lX\n", (unsigned long)&num2);
  (void)printf("string2 (uninitialized global char *) at              : 0x%12lX\n", (unsigned long)&string2);
  (void)printf("extern **environ at                                   : 0x%12lX\n", (unsigned long)&environ);
  (void)printf("\n");

  (void)printf("Initialized Data:\n");
  (void)printf("-----------------\n");
  (void)printf("num(initialized global int) at                        : 0x%12lX\n", (unsigned long)&num);
  (void)printf("string  (initialized global  char *) at               : 0x%12lX\n", (unsigned long)&string);
  (void)printf("\n");
  
  (void)printf("Test Segment\n");
  (void)printf("------------\n");
  (void)printf("func2 (function) at                                   : 0x%12lX\n", (unsigned long)&func2);
  (void)printf("func (function) at                                    : 0x%12lX\n", (unsigned long)&func);
  (void)printf("main (function) at                              : 0x%12lX\n", (unsigned long)&main);
  (void)printf("\n");

  return EXIT_SUCCESS;
}

void
func(){
  int fint;

  static int n = 1;
  (void)printf("func frame at                                         : 0x%12lX\n", (unsigned long)&fint);
  (void)printf("static int n within func at                           : 0x%12lX\n", (unsigned long)&n);
  
  n++;
  func2("from func");
}

void
func2(const char  *how){
  int fint;
  (void)printf("func2 (%s): frame at                                  : 0x%12lX\n", how, (unsigned long)&fint);
}
