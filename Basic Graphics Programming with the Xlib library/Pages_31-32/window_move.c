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
 
  //Window icon

  XWMHints *win_hints;

  static const unsigned char goose_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c,
   0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x80, 0x0f,
   0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07,
   0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0xf8, 0x01, 0x00, 0x00, 0xfc, 0x01,
   0x00, 0x00, 0xfc, 0x01, 0x00, 0x07, 0xfe, 0x01, 0x10, 0x07, 0xff, 0x00,
   0x78, 0x0e, 0xff, 0x00, 0x80, 0x9f, 0x7f, 0x00, 0x00, 0xfe, 0x3f, 0x00,
   0x00, 0xfc, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0xf0, 0x0f, 0x00,
   0x00, 0xe0, 0x3f, 0x00, 0x00, 0x80, 0xff, 0x01, 0x00, 0x00, 0xf8, 0x01,
   0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };
  int icon_bitmap_width = 32;
  int icon_bitmap_height = 31;

  Pixmap icon_pixmap = XCreateBitmapFromData(display, win, goose_bits, icon_bitmap_width,icon_bitmap_height);

  XCopyPlane(display, icon_pixmap, win, gc, 0, 0, icon_bitmap_width, icon_bitmap_height, 0, 0, 1); 
  if(!icon_pixmap){
    fprintf(stderr, "XCreateBitmapFromData - error creating pixmap\n");
    exit(1);
  }

  win_hints = XAllocWMHints();
  if(!win_hints){
    fprintf(stderr, "XallocWMHints - out of memory\n");
    exit(1);
  }

  win_hints->flags = IconPixmapHint;
  win_hints->icon_pixmap = icon_pixmap;
  
  XSetWMHints(display, win, win_hints);

  XSelectInput(display, win, ExposureMask);
  XEvent an_event;
  while(1){
    XNextEvent(display, &an_event);  
    break;
  }

  XMoveWindow(display,win,400,100);
  sleep(1);
  XMoveWindow(display,win,400,100);
  sleep(1);
  XMoveWindow(display,win,200,200);
  sleep(1);
  XFree(win_hints);
  XFlush(display);
  XCloseDisplay(display); 
}

