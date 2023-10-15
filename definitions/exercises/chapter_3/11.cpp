#include <iostream>
#include <stack>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string htmlEval(string htmlExpr){
  try{
    if(htmlExpr.size() == 0) {throw string("Input is of zero characters");}
  } catch (const std::exception& e){
    std::cout << "Error"<<endl;
  }
  stack<string> operandStack;
  string line;
  stringstream ss(htmlExpr);
  while(getline(ss,line, '\n')){
    if(line =="<html>"){
      operandStack.push(line);
    } else if(line == "<head>"){
        operandStack.push(line);
      }
      else if(line == "<title>"){
        operandStack.push(line);
      }
      else if(line == "<body>"){
        operandStack.push(line);
      }
      else if(line =="</html>"){
        if(operandStack.top() == "<html>"){
          operandStack.pop();
        };
      } else if(line == "</head>"){
        if(operandStack.top() == "<head>"){
          operandStack.pop();
        };
      }
      else if(line == "</title>"){
        if(operandStack.top() == "<title>"){
          operandStack.pop();
        };
      }
      else if(line == "</body>"){
        if(operandStack.top() == "<body>"){
          operandStack.pop();
        };
      }
   }
   if(operandStack.empty()){
     return "Perfect operating stack";
   } else {
     cout << "Issues in the stack with: " << endl;
     return operandStack.top();
   }
}

int main(){
  string text{"<html>\n<head>\n<title>\nExample\n</title>\n</head>\n<body>\n<h1>Hello, world</h1>\n</body>\n</hml>"};
  cout << htmlEval(text) << endl;
}

