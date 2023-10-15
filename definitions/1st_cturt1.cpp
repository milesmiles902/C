#include <CTurtle.hpp>
namespace ct = cturtle;

void spiral(ct::Turtle& turtle, int length){
  if(length>0){
    turtle.forward(length);
    turtle.right(90);
    spiral(turtle,length-5);
  }
}

int main(){
  ct::TurtleScreen screen;
  ct::Turtle turtle(screen);
  
  spiral(turtle,100);
  screen.bye();
  return s;
}
