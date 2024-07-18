#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char *argv[]){
  Display* display;

  display = XOpenDisplay(0);
  if (display == NULL){
    fprintf(stderr, "The X server connection faileed %s\n", "simey:0");
    exit(-1);
  }

  XCloseDisplay(display);
}
