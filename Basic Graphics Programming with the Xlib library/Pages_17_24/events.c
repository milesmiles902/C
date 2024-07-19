 #include <X11/Xlib.h>
 #include <stdio.h>
 #include <stdlib.h> 
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
 void handle_expose(Display* display, GC gc, GC rev_gc, XExposeEvent* expose_event,
		    unsigned int win_width, unsigned int win_height,
		    short pixels[1000][1000]){
   if (expose_event->count != 0)
     return;
   XDrawPoint(display, expose_event->window, gc, 5, 5);
   XDrawPoint(display, expose_event->window, gc, 5, win_height-5);
   XDrawPoint(display, expose_event->window, gc, win_width-5, 5);
   XDrawPoint(display, expose_event->window, gc, win_width-5, win_height-5);
   XDrawLine(display, expose_event->window, gc, 50, 0, 50, 200);
   XDrawLine(display, expose_event->window, gc, 0, 100, 200, 100);
   XDrawArc(display, expose_event->window, gc,
	    50-(30/2), 100-(30/2), 30, 30, 0, 360*64);
   XPoint points[] = {{0, 0},
   {15, 15},
   {0, 15},
   {0, 0}
   };
   int npoints = sizeof(points)/sizeof(XPoint);
   XDrawLines(display, expose_event->window, gc,
	      points, npoints, CoordModeOrigin);
   }
		    
		    
void handle_drag(Display* display, GC gc, GC rev_gc, XButtonEvent* drag_event, unsigned int win_width, unsigned int win_height,short pixels[1000][1000]){ 
  int x, y;
  x = drag_event->x;
  y = drag_event->y;
  switch (drag_event->state) {
    case Button1Mask: 
      XDrawPoint(display, drag_event->window, gc, x, y);
      pixels[x][y] = 1;
      break;
    case Button2Mask: 
      XDrawPoint(display, drag_event->window, rev_gc, x, y);
      pixels[x][y] = -1;
      break;
  }
}

void handle_button_down(Display* display, GC gc, GC rev_gc,
			XButtonEvent* button_event,
			unsigned int win_width, unsigned int win_height,
			short pixels[1000][1000]){ 
  int x, y;
  x = button_event->x;
  y = button_event->y;
  switch (button_event->button) {
    case Button1: 
      XDrawPoint(display, button_event->window, gc, x, y);
      pixels[x][y] = 1;
      break;
    case Button2: 
      XDrawPoint(display, button_event->window, rev_gc, x, y);
      pixels[x][y] = -1;
      break;
  }
}
void main(int argc, char* argv[]){ 
  Display* display; /* pointer to X Display structure. */
  int screen_num; 
  Window win; 
  unsigned int display_width,
  display_height; 
  unsigned int width, height; 
  char *display_name = getenv("DISPLAY"); 
  GC gc, rev_gc; 
  short pixels[1000][1000]; 
  { int x, y;
    for (x=0; x<1000; x++)
      for (y=0; y<1000; y++)
	pixels[x][y] = 0;
  }
  display = XOpenDisplay(display_name);
  if (display == NULL) {
    fprintf(stderr, "%s: cannot connect to X server '%s'\n",
	    argv[0], display_name);
    exit(1);
  }
  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);
  width = (display_width / 3);
  height = (display_height / 3);
  printf("window width - '%d'; height - '%d'\n", width, height);
  
  win = create_simple_window(display, width, height, 0, 0);
  gc = create_gc(display, win, 0);
  rev_gc = create_gc(display, win, 1);
  XSelectInput(display, win, ExposureMask | KeyPressMask |
  ButtonPressMask | Button1MotionMask |
  Button2MotionMask | StructureNotifyMask);
  printf("Mouse Click: Pixel invert\nKeyboard Press: Window exit\n");
  { int done = 0;
    XEvent an_event;
    while (!done) {
      XNextEvent(display, &an_event);
      switch (an_event.type) {
	case Expose:
	  handle_expose(display, gc, rev_gc, (XExposeEvent*)&an_event.xexpose,
			width, height, pixels);
	  break;
	case ConfigureNotify:
	  width = an_event.xconfigure.width;
	  height = an_event.xconfigure.height;
	  break;
	case ButtonPress:
	  handle_button_down(display, gc, rev_gc,
			     (XButtonEvent*)&an_event.xbutton,
			     width, height, pixels);
	  break;
	case MotionNotify:
	  handle_drag(display, gc, rev_gc,
		      (XButtonEvent*)&an_event.xbutton,
		      width, height, pixels);
	  break;
	case KeyPress:
	  done = 1;
	  break;
	default: 
	  break;
      } 
    }
    XFreeGC(display, gc);
    XFreeGC(display, rev_gc);
    XCloseDisplay(display);
  }
}
			  
			  
