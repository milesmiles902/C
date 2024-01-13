#include <CTurtle.hpp>
namespace ct = cturtle;

int main(){
  ct::TurtleSreen screen;
  ct::Turtle turtle(screen);

  ct::Polygon upside_down_triangle = {
    {0,0},
    {-5,-5},
    {5,-5}
  };
  turtle.shape(upside_down_triangle);

  for(int i=0;i<4;i++){
    int corner_stamp = turtle.stamp();
    turtle.forward(25);
    turtle.stamp();
    turtle.forward(25);
    turtle.right(90);
    turtle.clearstamp(corner_stamp);
  }
  turtle.clearstamps();
  screen.bye();
  return 0;
}
