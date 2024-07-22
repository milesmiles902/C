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
 
  //Pixmap Window
 
  Pixmap pixmap;
  Window root_win = DefaultRootWindow(display);
  
  int depth = DefaultDepth(display, DefaultScreen(display));

  Pixmap bitmap;
  unsigned int bitmap_width, bitmap_height;

  int hotspot_x, hotspot_y;

  int rc = XReadBitmapFile(display, root_win, "icon.bmp", &bitmap_width, &bitmap_height, &bitmap, &hotspot_x, &hotspot_y);


  pixmap = XCreatePixmap(display, root_win, 30, 40, depth);

    while(1){
    switch(rc){
      case BitmapOpenFailed:
        fprintf(stderr, "XReadBitmapFile - the file failed 'icon.bmp'.\n");
        break;
      case BitmapFileInvalid:
        fprintf(stderr,
                "XReadBitmapFile - file '%s' contains a valid bitmap/\n");
        break;
      case BitmapNoMemory:
        fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
        break;
      case BitmapSuccess:
        XDrawPoint(display,pixmap,gc,15,20);
        XCopyArea(display, pixmap, win, gc, 0, 0, bitmap_width, bitmap_height, 100, 50);

        break;
    }
  }
 
  sleep(2);
  XFreePixmap(display,pixmap);
  XFlush(display);
  XCloseDisplay(display); 
}

