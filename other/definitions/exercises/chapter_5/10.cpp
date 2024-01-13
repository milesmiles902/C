#include <iostream>
using namespace std;

int gcd(int a, int b){
  if(b==0)
    return a;
  return gcd(b, a%b);
}

int jug(int fromJug, int toJug, int d){
  int from,to=0;
  int amount = 1;
  while(from != d && to != d){
    int temp = min(from,toJug-to);
    to+=temp;
    from-=temp;
    amount++;
    if(from==d||to==d)
      break;
    if(from==0){
      from = fromJug;
    }
    if(toJug==to){
      to = 0;
      amount++;
    }
  }
  return amount;
}

int steps(int m, int n, int d){
  if(m>n)
    swap(m,n);
  if(d>n)
    return -1;
  if((d%gcd(n,m)) != 0)
    return -1;
  
  return min(jug(n,m,d),
         jug(m,n,d));
}

int main(){
  int jug1 = 4;
  int jug2 = 3;
  int amount = 2;
  if(steps(jug1,jug2,amount) == 2){
    cout << "The minimal steps is pouring Jug1 into Jug2" << endl;
    cout << "While the number of pours is" << endl;
    cout << jug(jug2,jug1,amount) << endl;
    if(jug1>jug2){
      cout << "The remaining amount of water in the larger jug is:" << jug1 % (steps(jug2,jug1,amount));
    } else {
      cout << "The remaining amount of water in the larger jug is" << (jug2 % (steps(jug2,jug1,amount)));
    }
  } else{
    cout << "The minimal steps is pouring Jug2 into Jug1" << endl;
    cout << "While the number of pours is" << endl;
    cout << jug(jug1,jug2,amount) << endl;
    if(jug1>jug2){
      cout << "The remaining amount of water in the larger jug is:" << (jug1 % (steps(jug1,jug2,amount)));
    } else {
      cout << "The remaining amount of water in the larger jug is" << (jug1 % (steps(jug1,jug2,amount)));
    }

  }
  return 0;
}
