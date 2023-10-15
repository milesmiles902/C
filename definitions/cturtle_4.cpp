#include <CTurtle.hpp>
namespace ct = cturtle;

int main(){
  ct::TurtleScreen screen;
  ct::Turtle turtle(screen);

  turtle.speed(ct::TS_SLOWEST);
  
  turtle.fillcolor({"purple"});
  
  turtle.begin_fill();
  
  for(int i=0;i<4;i++){
    turtle.forward(50);
    turtle.right(90);
  }
  turtle.end_fill();
  screen.bye();
  return 0;
}
