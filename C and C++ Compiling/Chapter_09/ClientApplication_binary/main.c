#include <stdio.h>
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"

int main(int argc, char *argv[]){
  shlib_function();
  shlibfirst_function();
  shlibsecond_function();
  shlibsecond_another_function();
  return 0;
}
