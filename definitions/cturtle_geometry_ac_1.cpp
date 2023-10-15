#include <CTurtle.hpp>
namespace ct = cturtle;

int main(){
  ct::TurtleScreen screen;
  ct::Turtle turtle(screen);

  ct::Polygon upside_down_triangle = {
    {0,0},
    {-5,-5},
    {5,-5}
  }
  
  turtle.shape(upside_down_triangle);
  turtle.forward(50);
  screen.bye();
  return 0;
}
