#include "stdio.h"

#if 1
#define FOR_EXPORT __attribute__ ((visibility("default")))
#else
#define FOR_EXPORT
#endif

alfunction1(void){
  printf("function1\n");
}

void mylocalfunction2(void){
  printf("function2\n");
}

void mylocalfunction3(void){
  printf("function3\n");
}

void FOR_EXPORT printMessage(void){
  printf("Running the function exported from the shared library\n");
}

