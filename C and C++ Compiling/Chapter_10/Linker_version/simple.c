#include <stdio.h>
#include "simple.h"


int first_function(int x){
  printf(" lib: %s\n", __FUNCTION__);
  return (x+1);
}

int second_function(int x){
  printf(" lib: %s\n", __FUNCTION__);
  return (x+2);
}

int third_functionn(int x){
  printf(" lib: %s\n", __FUNCTION__);
  return (x+3);
}


