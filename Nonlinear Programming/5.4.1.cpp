/*
Question 5.4.1:

/////////////////////////////////////////
//First Implementation of Newton's Method
/////////////////////////////////////////
*/

////////////////////////////
////g++ 5.4.1.cpp -std=c++11
////////////////////////////

#include <functional> //function
#include <iostream>   //cout
#include <cmath>      //standard math library, absolute, power, etc
#include <limits>     //epsilon, h in derivatives
#include <vector>     //vector, for variables
#include <iomanip>    //setprecision, for variable prints
#include <string>     //flags

using namespace std;

//Function aliases
typedef function<float(float,float)> RealFuncF;
typedef function<float(float,float)> RealFuncH;
typedef function<float(function<float(float,float)>,float,float)> RealFuncDerivativeF;
typedef function<float(function<float(float,float)>,float,float)> RealFuncDerivativeH;
//typedef function<float(function<float(float)>,float)> RealFuncSecondDerivativeH;
typedef function<float(function<float(float,float)>, \
                       function<float(float,float)>,             \
                       float,float,float)> RealFuncSecondDerivativeL;

//Function: f(x1,x2) = -x1*x2;
float FuncF(float x1, float x2){
  float val = -x1*x2;
  return val;
}

//Constraint: h(x1, x2) = 2 - x1 - x2
float FuncH(float x1, float x2){
  float val = 2-x1-x2;
  return val;
}

//A derivative of f(x1,x2) = -x1*x2;
float computeDerivativeF(RealFuncF f, float x1, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L;
  if(x1==0 && x2 == 0){
    L = 0;
  } else{
    L = (f(x1+h,x2)-f(x1,x2))/h + (f(x1,x2+h)-f(x1,x2))/h;
  }
  return L;
}

//A contraint derivative for h(x2) = x1+x2 = 2;
float computeDerivativeH(RealFuncH H, float x1, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L;
  if(x1 == 0 && x2 == 0){
    L = 0;
  } else {
    L = (H(x1+h,x2)-H(x1,x2))/h + (H(x1,x2+h)-H(x1,x2))/h;
  }
  return L;
}

//A second derivative for the Lagrangian equation: L(x1,x2,p,lambda) = f(x1,x2) + lambda*h(x2)
float computeSecondDerivativedL(RealFuncF f, RealFuncH H, float x1, float x2, float lambda){
  float h = sqrt(numeric_limits<float>::epsilon());
  //float L = (f(x1+h,x2)-2*f(x1,x2)+f(x1-h,x2))/(h*h) + (f(x1,x2+h)-2*f(x1,x2)+f(x1,x2-h))/(h*h) + lambda*(((H(x1+h, x2)-2*H(x1,x2)+H(x1-h,x2))/(h*h))+(H(x1, x2+h)-2*H(x1,x2)+H(x1,x2-h))/(h*h));
  float L = (f(x1+h,x2)-f(x1,x2))/h+(f(x1,x2+h)-f(x1,x2))/h + lambda*(H(x1+h,x2)-H(x1,x2)/h + (H(x1,x2+h)-H(x1,x2))/h);
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
      vector2[j] += matrix[j][i]*vector1[i];
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
float evaluateMinimum(RealFuncF f, RealFuncH h, RealFuncDerivativeF dF,RealFuncDerivativeH dH, RealFuncSecondDerivativeL ddL, float x1, float x2, float lambda, string flag1){
  int c = 1;
  float determinant, dx=0;
  
  //A First Implementation of Newton's Method:
  ///////////////////////
  //A solution for: A*x=b 
  //
  //                |H^k N^k|*|  dx^k   | = -| delL(x1^k,x2^k,lambda)|
  //                |N^k  0 | |dlambda^k|    |       h(x^k)          |
  //
  //                where H^k = del[delL(x,lambda)] and N^k = delh(x)
  //          
  // Notes: 1) First Implementation of Newton's method requires a 2x2 matrix with solutions from an equation system. 
  //        2) The function returns dx^k or dlambda^k
  //
  float** A = makeMatrix(2);
  setMatrix(A,2);
  
  float* X = makeVector(2);
  setVector(X,2);
  
  float *b = makeVector(2);
  setVector(b,2);
  
  float **Am1 = makeMatrix (3);
  
  X[0]=0;
  X[1]=0;
  
  //Left-hand Matrix
  A[0][0]=ddL(f,h,x1,x2,lambda);
  A[0][1]=dH(h,x1,x2);
  A[1][0]=dH(h,x1,x2);
  A[1][1]=0;
    
  //Right-hand Matrix
  b[0]= -dF(f,x1,x2)+lambda*dH(h,x1,x2);
  b[1] = -h(x1,x2);

  //The determinant 
  determinant = A[0][0]*A[1][1]-A[1][0]*A[0][1];
  
  //A flag for a zero determinant
  if(determinant == 0){
    X[0]=b[0]/A[0][0];
    X[1]=lambda;
  } else{
    //Otherwise proceed with a system of equations
    Am1 = inverseA(A);
    multiply(Am1,b,X,2,2,2); 
  }
  
  if(flag1 == "lambda"){
    return X[1]; 
  } else if(flag1 == "x"){
    return X[0]; 
  }
  return 0;
}

float calculationByHand(float x1, float x2, float lambda, string flag1){
  // A solution by hand has lambda^{k+1} = 1/(N^k*N^k/H^k)*(h(x^k)-N^k*delf(x^k)/H^k)
  //                                     = -1
  //                             
  //                             x^{k+1} = x^k - delL(x^k,lambda^{k+1})/H^k
  //                                     = x^k - (x2^k + x1^k + 2*lambda^k)/2
  //
  // The matrix calculation reduced by hand on paper for comparison.
  
  if(flag1 == "lambda"){
    return -1;
  } else if(flag1 == "x"){
    return (x2+x1+2*lambda)/2;
  }
 return -1;
}

void iterationDriver(RealFuncF f, RealFuncH h, RealFuncDerivativeF dF,RealFuncDerivativeH dH, RealFuncSecondDerivativeL ddL, float x1, float x2, float lambda, float precision){
  float x1i, x2i, x1k, x2k, lambdakx1, lambdakx2;

  x1i = x1;
  x2i = x2;
  lambdakx1 = lambda;
  lambdakx2 = lambda;

  for(int i=0;;i++){
    lambdakx1 = calculationByHand(x1,x2,lambdakx1,"lambda");
    x1k = calculationByHand(x1,x2,lambdakx1,"x");

    lambdakx2 = calculationByHand(x1,x2,lambdakx2,"lambda");
    x2k = calculationByHand(x1,x2,lambdakx2,"x");
   
    x1-=x1k;
    x2-=x2k;
 
    if(abs(2-x1-x2)< precision){
      cout << "A pre-evaluated Newton's First Implementation ended in " << i+1 << " iterations." << endl;
      cout << "x1 is: " << x1 << endl;
      cout << "x2 is: " << x2 << endl;
      cout << endl;
      break;
    }
  }  
 
  x1 = x1i;
  x2 = x2i;

  for(int i=0;i<1;i++){
    lambdakx1=evaluateMinimum(f,h,dF,dH,ddL,x1,x2,lambdakx1,"lambda");
    x1k=evaluateMinimum(f,h,dF,dH,ddL,x1,x2,lambdakx1,"x");

    lambdakx2=evaluateMinimum(f,h,dF,dH,ddL,x1,x2,lambdakx2,"lambda");
    x2k=evaluateMinimum(f,h,dF,dH,ddL,x1,x2,lambdakx2,"x");

    x1-=x1k;
    x2-=x2k;

    if(abs((2-x1-x2))< precision){
      cout << "An equation system with matrix inversion ended in " << i+1 << " iterations." << endl;
      cout << "x1 is: " << x1 << endl;
      cout << "x2 is: " << x2 << endl;
      return;
    }
  }
}


//The main with initial conditions
int main(){
  RealFuncF f{FuncF};
  RealFuncH h{FuncH};
  RealFuncDerivativeF dF{computeDerivativeF};
  RealFuncDerivativeH dH{computeDerivativeH};
  RealFuncSecondDerivativeL ddL{computeSecondDerivativedL};
  
  float x1=1.01, x2=0.01, lambda0 = 0.1, precision = 10e-5;
  cout << endl << "Function f(x1,x2,p) = -x1*x2" << endl;
  cout <<"Constraint: x1 + x2 = 2" << endl;
  cout << endl;
  cout <<"/////////////////////////////////////////////////////////" << endl;
  cout <<"/////////////////////////////////////////////////////////" << endl << endl;
  cout <<"Initial x1: " << setprecision(3) << x1 << endl;
  cout <<"Initial x2: " << setprecision(3) << x2 << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  iterationDriver(f,h,dF,dH,ddL,x1,x2,lambda0,precision);

  return 0; 
}
