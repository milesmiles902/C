#include <X11/Xlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 Display* display; 
  int screen_num; 
  Window win;
  GC gc;
  unsigned int display_width,
               display_height; 
  unsigned int width, height; 
  unsigned int win_x, win_y; 
  unsigned int win_border_width;
  char *display_name = getenv("DISPLAY"); 
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
  win_x = 0;
  win_y = 0;
  win_border_width = 2;
  
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                                                win_x, win_y, 
                                                width, height, win_border_width,
                                                BlackPixel(display, screen_num),
                                                WhitePixel(display, screen_num));

  XGCValues values;
  values.cap_style = CapButt;
  values.join_style = JoinBevel;
  unsigned long valuemask = GCCapStyle|GCJoinStyle;
 
  gc = XCreateGC(display, win, valuemask, &values);
  if(gc < 0){
    fprintf(stderr, "XcreateGc: \n");
  }
  XMapWindow(display, win);
  while(1){
   // XNextEvent(display,
    XDrawPoint(display,win,gc,5,5);
    XDrawLine(display,win,gc,20,20,40,100);
    int x = 30, y = 40;
    int h = 15, w = 45;
    int angle1 = 0, angle2 = 2.109;
    XDrawArc(display,win,gc, x-(w/2),y-(h/2),w,h,angle1,angle2);
    XDrawArc(display,win,gc,50-(15/2),100-(15/2),15,15,0,360*64);

    {
      XPoint points[] = {{0,0},
                         {15,15},
                         {0,15},
                         {0,0}
                        };
      int npoints = sizeof(points)/sizeof(XPoint);
      XDrawLines(display,win,gc,points,npoints,CoordModeOrigin);
  }
    XDrawRectangle(display,win,gc,120,150,50,60);
    XFillRectangle(display,win,gc,60,150,50,60);

  }
  XCloseDislay(display);
}
