#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char*argv[]){
    Display* display = XOpenDisplay(NULL);
    Window win;
 
    int screen_num;

    int win_width;
    int win_height;   
 
    int win_x;
    int win_y;

    int win_border_width;

    screen_num = DefaultScreen(display); 

    win_width = DisplayWidth(display, screen_num)/3;
    win_height = DisplayHeight(display, screen_num)/3;

    win_x = win_y = 0;
    win_border_width = 4;

    win = XCreateSimpleWindow( display, 
                               RootWindow(display,screen_num),
                               win_x, win_y, 
                               win_width, win_height, win_border_width, 
                               BlackPixel(display, screen_num), 
                               WhitePixel(display, screen_num));

    XMapWindow(display, win);
    XSync(display,False);
    sleep(2);
    XCloseDisplay(display);
    return 0;
}
