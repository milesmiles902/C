#include "sharedLibExports.h"
#include <stdio.h>
#include <unistd.h>

#ifdef __LP64__
const char service_interp[] __attribute__((section(".interp"))) = "/usr/lib64/libc.so.6";
#else
const char service_interp[] __attribute__((section(".interp"))) = "/usr/lib64/libc.so";
#endif

void printfMessage(void){
  printf("The function exported from the shared library.\n");
}

int main(int argc, char *argv[]){
  printf("Shared library %s() function\n", __FUNCTION__);
  _exit(0);
}

