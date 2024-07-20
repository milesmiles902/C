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
  int x,y;
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

  XSync(display, False); 
 
  XFontStruct* font_info;
  char* font_name = "*bitstream-courier*";                                //cat /usr/share/X11/fonts/Type1/fonts.dir
  font_info = XLoadQueryFont(display, font_name);
  
  if(!font_info){
    fprintf(stderr, "XLoadQueryFont: failed loading font '%s'\n", font_name);
  }
     
  char *text_string = "middle of the road";
  int string_width = XTextWidth(font_info, text_string, strlen(text_string));
  int font_height = font_info->ascent + font_info->descent;
  
  x = (width - string_width)/2;
  y = (width-font_height)/2;
  XSetFont(display,gc,font_info->fid);
  XSelectInput(display, win, ExposureMask | ButtonPress);
  XMapWindow(display, win);
  
  XEvent an_event;
  while(1){
    XNextEvent(display, &an_event);
    if(an_event.type == Expose){
      XDrawString(display, win, gc, x, y, text_string, strlen(text_string));
    }
    if(an_event.type == ButtonPress) break;   
  }

  XFlush(display);


  XCloseDisplay(display);
 
}

