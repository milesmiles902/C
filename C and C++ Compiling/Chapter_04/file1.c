#include <stdio.h>

void func1();
extern void func2();

void func1(){
  printf("funcln");
}

int main(void){
  func1();
  func2();
}
