#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char *argv[]){
  int screen_num;
  int screen_width;
  int screen_height;

  Window root_window;

  unsigned long white_pixel;
  unsigned long black_pixel;

  Display *display = XOpenDisplay(0);;

  screen_num = DefaultScreen(display);

  screen_width = DisplayWidth(display, screen_num);
  
  screen_height = DisplayHeight(display, screen_num);
  
  root_window = RootWindow(display, screen_num);
  
  white_pixel = WhitePixel(display, screen_num);

  black_pixel = BlackPixel(display, screen_num);

}
