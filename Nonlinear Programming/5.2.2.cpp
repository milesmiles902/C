/*
Question 5.2.2:

Function: f(x1,x2) = (1/2)(x1*x1+|x2|^p) + 2x2

Constraint: x2=0

a) Lagrange function: L(x1,x2,lambda) = f(x1,x2) + lambda*x2

                                      = (1/2)(x1*x1+|x2|^p) + 2x2 + lambda*x2

                 dL(x1,x2,lambda)/dx1 = x1

                                      = 0
 
                 dL(x1,x2,lambda)/dx2 = (p/2)*|x2|^{p-1} + 2 + lambda

                                      = 0

                 (x1*,x2*,lambda*) = (0,0,-2)

b) //Multiplier Method 
*/

////////////////////////////
////g++ 5.1.1.cpp -std=c++11
////////////////////////////

#include <functional> //function
#include <iostream>   //cout
#include <cmath>      //standard math library, absolute, power, etc
#include <limits>     //epsilon, h in derivatives
#include <vector>     //vector, for variables
#include <iomanip>    //setprecision, for variable prints

using namespace std;

//Function aliases
typedef function<float(float,float,float)> RealFuncF;
typedef function<float(float)> RealFuncH;
typedef function<float(function<float(float,float,float)>,float,float,float)> RealFuncDerivativeF;
typedef function<float(function<float(float)>,float)> RealFuncDerivativeH;
typedef function<float(function<float(float)>,float)> RealFuncSecondDerivativeH;
typedef function<float(function<float(float,float,float)>, \
                       function<float(float)>,             \
                       float,float,float,float)> RealFuncSecondDerivativeL;

//Function: f(x1,x2) = ( x1*x1 + |x2|^p) )/2 + 2*x2;
float FuncF(float x1, float x2, float p){
  float val = (x1*x1 + pow(abs(x2),p) )/2 + 2*x2;
  return val;
}

//Constraint: h(x2) = x2 = 0
float FuncH(float x2){
  return x2;
}

//A derivative of f(x1,x2) = ( x1*x1 + |x2|^p) )/2 + 2*x2;
float computeDerivativeF(RealFuncF f, float x1, float x2, float p){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L;
  if(x1==0 && x2 == 0){
    L = 0;
  } else{
    L = (f(x1+h,x2,p)-f(x1,x2,p))/h + (f(x1,x2+h,p)-f(x1,x2,p))/h;
  }
  return L;
}

//A contraint derivative for h(x2) = x2 = 0;
float computeDerivativeH(RealFuncH H, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (H(x2+h)-H(x2))/h;
  return L;
}

//A contraint second derivative for h(x2) = x2 = 0;
float computeSecondDerivativeH(RealFuncH H, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (H(x2+h)-2*H(x2)+H(x2-h))/(h*h);
  return L;
}

//A second derivative for the Lagrangian equation: L(x1,x2,p,lambda) = f(x1,x2) + lambda*h(x2)
float computeSecondDerivativedL(RealFuncF f, RealFuncH H, float x1, float x2, float p, float lambda){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (f(x1+h,x2,p)-2*f(x1,x2,p)+f(x1-h,x2,p))/(h*h) + (f(x1,x2+h,p)-2*f(x1,x2,p)+f(x1,x2-h,p))/(h*h) + lambda*(H(x2+h)-2*H(x2)+H(x2-h))/(h*h);
  return L;
}

//A matrix double pointer
float **makeMatrix(int size){
  float **matrix;
  matrix = new float* [size];
  
  for(int i=0;i<size;i++){
    matrix[i]=new float[size];
  }
  return matrix;
}

//A matrix fill with zeros
void setMatrix(float** matrix, int size){
  float temp = 0.0;

  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      matrix[i][j]=temp;
    }
  }
}

//A vector fill with zeros
void setVector(float *vector, int size){
  float temp=0.0;
  for(int i=0;i<size;i++){
    vector[i]=temp; 
  }
}

//A vector machine
void makeVector(float* vector){
  for(int i=0;i<3;i++){
    vector[i] =0;
  }
}

//A vector pointer
float *makeVector(int size){
  float* vector = new float[size];
  return vector;
}

//A matrix delete
void deleteMatrix(float **matrix, int size){
  for(int i=0;i<size;i++){
    delete matrix[i];
  }
  delete[] matrix;
}

//A vector delete
void deleteVector(float* vector, int size){
  delete[] vector;
}

//A matrix[2x2] evaluator
float twobytwoDeterminant(float a, float b, float c, float d){
  return a*d-b*c;
}

//A matrix and vector multipler
float* multiply(float** matrix, float* vector1, float* vector2, int rows, int cols, int vector_size){
  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++){
      vector2[i] += matrix[i][j]*vector1[j];
    }
  }
  
  return vector2;
}

//Inverse of a matrix
float **inverseA(float ** A){
  float** cofactor_transposed = makeMatrix(2);
  float** Am1 = makeMatrix(2);
  float determinant = 0;
 
  //Transpose
  cofactor_transposed[0][9]=A[1][1];
  cofactor_transposed[0][1]=A[1][0];
  cofactor_transposed[1][0]=A[0][1];
  cofactor_transposed[1][1]=A[0][0];
 
  //Determinant
  determinant = cofactor_transposed[0][0]*cofactor_transposed[1][1]-cofactor_transposed[1][0]*cofactor_transposed[0][1];
  
  //Singular Matrix; Determinant is zero
  if(determinant == 0){
    return cofactor_transposed;
  } 
  else{
      //Determinant is not zero
      for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
          Am1[i][j] = cofactor_transposed[i][j]/(cofactor_transposed[0][0]*cofactor_transposed[1][1]-cofactor_transposed[1][0]*cofactor_transposed[0][1]);
        }
      }
  }
  
  return Am1;
}

//Find the minimum for Multiplier Methods
void evaluateMinimum(RealFuncF f, RealFuncH h, RealFuncDerivativeF dF,RealFuncDerivativeH dH, RealFuncDerivativeH ddH,RealFuncSecondDerivativeL ddL, float x1, float x2, float p, float lambda0, float precision){
  int c = 1;
  float determinant, dx=0, dlambda=lambda0;
  
  //Multiplier Methods:
  ////////////////////
  //A solution for: A*x=b 
  //
  //                |d[delL(x1,x2,p,lambda)]/dx   d[delh(x)]/dx|*|  dx   | = | delL(x1,x2,p,lambda)|
  //                |       d[delh(x)]/dx                0     | |dlambda|   |       h(x)          |
  //
  // Notes: In Multiplier Methods, a 2x2 matrix has solutions from a system of equations. 
  //        
  //        Although, problem cases arise from Multiplier Methods by system of equations: 
  //           A) The determinant is zero. The matrix inverse, A^-1, for the solution, x=b*A^-1 has zero in the determinant. A system of equations solution requires a flag for singular determinants. 
  //           
  //           B) The constraint demonstrates no dependency between variables, h(x)=x2=0. Without x1 and x2 in the constraint, the x-values increment by select gradient methods prior to implementation.
  //           
  //           C) Start conditions. A Multiplier Method in the book, lambda=lambda0+c*h(x), where lambda0 = 0, and h(x)=0 are zero. The system of equations has row with zeros. 
  //           
  //           D) Sometimes second derivatives in the Lagrangian have no solutions. A case with absolute symbols in the function generates unusual outcomes.
  
  //           A modified-Newton's step was choice for iteration, x_{n+1} = x_n - delL(x1,x2,p,lambda)/d[delL(x1,x2,p,lambda)]/dx 

  float** A = makeMatrix(2);
  setMatrix(A,2);
  
  float* X = makeVector(2);
  setVector(X,2);
  
  float *b = makeVector(2);
  setVector(b,2);
  
  float **Am1 = makeMatrix (3);
  
  X[0]=5;
  X[1]=lambda0+c*h(x2);

  for(int i=0;;i++){
  
    //Left-hand Matrix
    A[0][0]=ddL(f,h,x1,x2,p,X[1]);
    A[0][1]=-ddH(h,x2);
    A[1][0]=-ddH(h,x2);
    A[1][1]=0;
 

    //Right-hand Matrix
    b[0]= dF(f,x1,x2,p)+X[1]*dH(h,x2);
    b[1] = h(x2);
   
    //The determinant 
    determinant = A[0][0]*A[1][1]-A[1][0]*A[0][1];
    
    //A flag for a zero determinant
    if(determinant == 0){
      X[0]=b[0]/A[0][0];
      X[1]=lambda0+c*h(x2);
    } else{
      //Otherwise proceed with a system of equations
      Am1 = inverseA(A);
      multiply(Am1,b,X,2,2,2);
    }
 
    dx = X[0];
    dlambda = X[1];

    //New x1
    x1-=(dF(f,x1,x2,p)+X[1]*dH(h,x2))/ddL(f,h,x1,x2,p,X[1]);
    //New x2
    x2=0;
    if(x1<0){ x1 = 0;}
    //A solution check for convergence
    if(abs(dF(f,x1,x2,p))<precision){
      cout << endl;
      cout <<"Multiplier method with convergence factor (p = "<< p << "):" << endl;
      cout <<"  Iteration total: " << i+1 << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1: " << x1 << " x2: " << x2 << endl;
      cout << endl;
      return;
    } 
  }
  return;
}

//The main with initial conditions
int main(){
  RealFuncF f{FuncF};
  RealFuncH h{FuncH};
  RealFuncDerivativeF dF{computeDerivativeF};
  RealFuncDerivativeH dH{computeDerivativeH};
  RealFuncDerivativeH ddH{computeSecondDerivativeH};
  RealFuncSecondDerivativeL ddL{computeSecondDerivativedL};
  
  float x1=1, x2=0, lambda0 = 0, p=1.5, precision = 10e-5;
  cout << endl << "Function f(x1,x2,p) = (1/2)(x1^2 + |x2|^p)+2*x2" << endl;
  cout <<"Constraint: x2 = 0" << endl;
  cout << endl;
  cout <<"/////////////////////////////////////////////////////////" << endl;
  cout <<"/////////////////////////////////////////////////////////" << endl << endl;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial p: " << p << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddH,ddL,x1,x2,p,lambda0,precision);

  p = 2;
  cout <<"/////////////////////////////////////////////////////////" << endl << endl;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial p: " << p << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddH,ddL,x1,x2,p,lambda0,precision);

  p = 3;
  cout <<"/////////////////////////////////////////////////////////" << endl << endl;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial p: " << p << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddH,ddL,x1,x2,p,lambda0,precision);
  cout <<"/////////////////////////////////////////////////////////" << endl << endl;

  cout <<"The initial conditions from the book produce a zero determinant solution and an exact solution in one-step. Test cases with other initial conditions functioned with the prior code.";  
  return 0; 
}

/* Part c) The case when p=1 is a flag in the computeDerivativeF function because a non-continous derivative. Although, the function's slope equals from the left and right. The flag appeared because "not a real number [NaN]" issues.
 */
