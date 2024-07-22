#include <X11/Xutil.h>
#include <X11/Xlib.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
#include <unistd.h>		

Window create_simple_window(Display* display, int width, int height, int x, int y){
  int screen_num = DefaultScreen(display);
  int win_border_width = 2;
  Window win;
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));

  XMapWindow(display, win);

  XFlush(display);

  return win;
}

GC create_gc(Display* display, Window win, int reverse_video){
  GC gc;			
  unsigned long valuemask = 0;		
					
  XGCValues values;			
  unsigned int line_width = 2;		
  int line_style = LineSolid;	
  int cap_style = CapButt;	
  int join_style = JoinBevel;		
  int screen_num = DefaultScreen(display);

  gc = XCreateGC(display, win, valuemask, &values);
  if (gc < 0) {
	fprintf(stderr, "XCreateGC: \n");
  }

  if (reverse_video) {
    XSetForeground(display, gc, WhitePixel(display, screen_num));
    XSetBackground(display, gc, BlackPixel(display, screen_num));
  }
  else {
    XSetForeground(display, gc, BlackPixel(display, screen_num));
    XSetBackground(display, gc, WhitePixel(display, screen_num));
  }

  XSetLineAttributes(display, gc,
                     line_width, line_style, cap_style, join_style);

  XSetFillStyle(display, gc, FillSolid);

  return gc;
}

void main(int argc, char* argv[]){
  Display* display;
  int screen_num;		
  Window win;			
  unsigned int win_width, win_height;	
  char *display_name = getenv("DISPLAY");  
  GC gc;			
			 
  XFontStruct* font_info;       

  display = XOpenDisplay(display_name);
  if (display == NULL) {
    fprintf(stderr, "%s: cannot connect to X server '%s'\n", argv[0], display_name);
    exit(1);
  }

  screen_num = DefaultScreen(display);
  win_width = DisplayWidth(display, screen_num)/3;
  win_height = DisplayHeight(display, screen_num)/3;


  win = create_simple_window(display, win_width, win_height, 0, 0);

  gc = create_gc(display, win, 0);
 
  //Color Foreground

  Colormap screen_colormap = DefaultColormap(display, DefaultScreen(display));
 
  XColor screen_color_1;
  screen_color_1.red = 20000;
  screen_color_1.green = 10000;
  screen_color_1.blue = 0; 
  XAllocColor(display, screen_colormap, &screen_color_1);
  XSetForeground(display, gc, screen_color_1.pixel);
 
  XSelectInput(display, win, ExposureMask);
  XEvent an_event;
  while(1){
    XNextEvent(display, &an_event);  
    break;
  }

  sleep(5);
  XFlush(display);
  XCloseDisplay(display); 
}

