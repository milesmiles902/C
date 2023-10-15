//Converts an infix expression to a postfix expression.

#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

string infixToPostfix(string infixexpr) {
    //performs the postfix process.
    unordered_map <char,int> prec;
    prec['*']=3;
    prec['/']=3;
    prec['+']=2;
    prec['-']=2;
    prec['(']=1;
    stack<char> opStack;
    vector<char> postfixVector;
    string letsnums = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   
    try {
      if(infixexpr.size() == 0){throw string("Input is of zero characters");}
    } catch (const std::exception& e){
      std::cout << "Error";
    };
    
    for (char token:infixexpr) {
        //for each character in infixexpr
        if (token == ' ') {
            continue;
        }
        else if (letsnums.find(token)<=letsnums.length()) { //finds if the token is inside of letsnums
            postfixVector.emplace_back(token); // appends to the end of the container.
        } else if (token == '(') {
            opStack.push(token);
        } else if (token == ')') {
            char topToken;
            topToken = opStack.top();
            opStack.pop();
            while (topToken != '(') {
                postfixVector.emplace_back(topToken);
                topToken=opStack.top();
                opStack.pop();
            }
        } else { //if the token is not inside of letsnums.
            while (!opStack.empty() && (prec[opStack.top()]>=prec[token])) //while the stack is not empty and
                                                                           //the top item of the stack is on a
                                                                           //higher level of PEMDAS than token.
            {
                postfixVector.emplace_back(opStack.top());
                opStack.pop();
                }
            opStack.push(token);
        }
    }
    while (!opStack.empty()) {
        postfixVector.emplace_back(opStack.top());
        opStack.pop();
    }

    string s(postfixVector.begin(),postfixVector.end());

    return s;
}

int main() {
    cout <<"infix: A * B + C * D\n" << "postfix: ";
    cout << infixToPostfix("A * B + C * D") << endl;
    cout << "infix: ( A + B ) * C - ( D - E ) * ( F + G )\n" << "postfix: ";
    cout << infixToPostfix("( A + B ) * C - ( D - E ) * ( F + G )") << endl;
    cout << "Error check: A`B`C\n" << "postfix: ";
    cout << infixToPostfix("") << endl;
    return 0;
}

