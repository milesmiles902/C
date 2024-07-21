#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>		
#include <unistd.h>		

#include "icon.bmp"

Window create_simple_window(Display* display, int width, int height, int x, int y){
  int screen_num = DefaultScreen(display);
  int win_border_width = 2;
  Window win;

  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));

  XSetTransientForHint(display, win, RootWindow(display, screen_num));

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

void
main(int argc, char* argv[])
{
  Display* display;		
  int screen_num;	
  Window win;			
  unsigned int display_width,
               display_height;	
  unsigned int win_width,
	       win_height;	
  char *display_name = getenv("DISPLAY");  
  GC gc;			

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
  printf("window width - '%d'; height - '%d'\n", win_width, win_height);
  win = create_simple_window(display, win_width, win_height, 0, 0);

  gc = create_gc(display, win, 0);
  XSync(display, False);

  {
    XTextProperty window_name_property;
    XTextProperty icon_name_property;
    XSizeHints* win_size_hints;
    XWMHints* win_hints;
    Pixmap icon_pixmap;

    char* window_name = "hello, world";
    char* icon_name = "small world";

    int rc = XStringListToTextProperty(&window_name,
                                       1,
                                       &window_name_property);
    if (rc == 0) {
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }
    rc = XStringListToTextProperty(&icon_name,
                                   1,
                                   &icon_name_property);
    if (rc == 0) {
        fprintf(stderr, "XStringListToTextProperty - out of memory\n");
        exit(1);
    }

    XSetWMName(display, win, &window_name_property);
    XSetWMIconName(display, win, &icon_name_property);

    win_size_hints = XAllocSizeHints();
    if (!win_size_hints) {
        fprintf(stderr, "XAllocSizeHints - out of memory\n");
        exit(1);
    }

    win_size_hints->flags = PSize | PMinSize;
    win_size_hints->min_width = 300;
    win_size_hints->min_height = 200;
    win_size_hints->base_width = 400;
    win_size_hints->base_height = 250;

    XSetWMNormalHints(display, win, win_size_hints);
    
    XFree(win_size_hints);

    icon_pixmap = XCreateBitmapFromData(display,
                                        win,
                                        icon_bitmap_bits,
                                        icon_bitmap_width,
                                        icon_bitmap_height);
    if (!icon_pixmap) {
        fprintf(stderr, "XCreateBitmapFromData - error creating pixmap\n");
        exit(1);
    }

    win_hints = XAllocWMHints();
    if (!win_hints) {
        fprintf(stderr, "XAllocWMHints - out of memory\n");
        exit(1);
    }

    win_hints->flags = IconPixmapHint | StateHint | IconPositionHint;
    win_hints->icon_pixmap = icon_pixmap;
    win_hints->initial_state = IconicState;
    win_hints->icon_x = 0;
    win_hints->icon_y = 0;

    XSetWMHints(display, win, win_hints);

    XFree(win_hints);
  }

  XFlush(display);

  sleep(25);

  XCloseDisplay(display);
}
