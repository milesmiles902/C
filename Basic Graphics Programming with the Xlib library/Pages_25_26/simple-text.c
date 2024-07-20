
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
  unsigned int display_width,
               display_height;	
  unsigned int win_width,
	       win_height;	
  char *display_name = getenv("DISPLAY");  
  GC gc;			
			 
  XFontStruct* font_info;       
  char *font_name = "fixed";

  display = XOpenDisplay(display_name);
  if (display == NULL) {
    fprintf(stderr, "%s: cannot connect to X server '%s'\n",
            argv[0], display_name);
    exit(1);
  }

  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);

  win_width = (display_width / 3);
  win_height = (display_height / 3);

  printf("display width - '%d'; height - '%d'\n", display_width, display_height);
  printf("window width - '%d'; height - '%d'\n", win_width, win_height);

  win = create_simple_window(display, win_width, win_height, 0, 0);

  gc = create_gc(display, win, 0);
  XSync(display, False);

  font_info = XLoadQueryFont(display, font_name);
  if (!font_info) {
      fprintf(stderr, "XLoadQueryFont: failed loading font '%s'\n", font_name);
      exit(-1);
  }
  XSelectInput(display, win, ExposureMask);
  XSetFont(display, gc, font_info->fid);
  XEvent an_event;
  while(1){
    XNextEvent(display, &an_event);    
    if(an_event.type == Expose){
    int x, y;
    char* text_string;
    int string_width;
    int font_height;

    font_height = font_info->ascent + font_info->descent;

    text_string = "hello world";
    x = 0;
    y = font_height;
    XDrawString(display, win, gc, x, y, text_string, strlen(text_string));

    text_string = "middle of the road";
    
    string_width = XTextWidth(font_info, text_string, strlen(text_string));
    x = (win_width - string_width) / 2;
    y = (win_height + font_height) / 2;
    XDrawString(display, win, gc, x, y, text_string, strlen(text_string));
    }
  }

  XFlush(display);

  sleep(4);

  XCloseDisplay(display);
}

