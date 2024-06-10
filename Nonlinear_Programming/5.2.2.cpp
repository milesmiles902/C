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

#include <functional>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

typedef function<float(float,float,float)> RealFuncF;
typedef function<float(float)> RealFuncH;
typedef function<float(function<float(float,float,float)>,float,float,float)> RealFuncDerivativeF;
typedef function<float(function<float(float)>,float)> RealFuncDerivativeH;
typedef function<float(function<float(float,float,float)>, \
                       function<float(float)>,             \
                       function<float(function<float(float,float,float)>,float,float,float)>, 
                       function<float(function<float(float)>,float)>,
                       float,float,float,float)> RealFuncSecondDerivativeL;

float FuncF(float x1, float x2, float p){
  float val = (x1*x1 + pow(abs(x2),p) )/2 + 2*x2;
  return val;
}

float FuncH(float x2){
  float val = 0;
  return val;
}

float computeDerivativeF(RealFuncF f, float x1, float x2, float p){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (f(x1+h,x2,p)-f(x1,x2,p))/h + (f(x1,x2+h,p)-f(x1,x2,p))/h;
  return L;
}

float computeDerivativeH(RealFuncH H, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (H(x2+h)-H(x2))/h;
  return L;
}

float computeSecondDerivativedL(RealFuncF f, RealFuncH H, RealFuncDerivativeF df, RealFuncDerivativeH dH, float x1, float x2, float p, float lambda){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (df(f, x1+h,x2,p)-df(f, x1,x2,p))/h + (df(f, x1,x2+h,p)-df(f, x1,x2,p))/h + lambda*(dH(H, x2+h)-dH(H, x2))/h;
  return L;
}

//Line minimization: https://en.wikipedia.org/wiki/Line_search
float lineMin(RealFuncF f, RealFuncH H, float d, float x1, float x2, float p,float lambda){
  float x=0,h=0,alpha=0,idx=1,min=0;
      min=f(x1+alpha*d,x2+alpha*d,p)+lambda*H(x2);
      for(int k=2;k<=100;k++){
        alpha+=1/100;
        h=f(x1+alpha*d,x2+alpha*d,p) + lambda*H(x2);
        if(h<min){
          min=h;
          idx=k;
        }
      }
      return idx*1/100;
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

void evaluateMinimum(RealFuncF f, RealFuncH h, RealFuncDerivativeF dF,RealFuncDerivativeH dH,RealFuncSecondDerivativeL ddL, float x1, float x2, float p, float lambda0, float precision){
  int c = 1;
  float determinant, dx=0, alpha=1, dlambda=lambda0;
  
  //Multiplier Methods:
  ////////////////////
  //A solution for: A*x=b 
  //
  //                |d[delL(x1,x2,p,lambda)]/dx   d[delh(x)]/dx|*|  dx   | = | delL(x1,x2,p,lambda)|
  //                |       d[delh(x)]/dx                0     | |dlambda|   |       h(x)          |
  //
  // Notes: In Multiplier Methods, a 2x2 matrix has solutions from by a system of equations. 
  //        
  //        Although, problem cases arise from systems of equations: 
  //           A) The determinant is zero. The matrix inverse, A^-1, for the solution, x=b*A^-1 has a zero determinant. A system of equations solves with a flag for singular determinants. 
  //           B) The constraint demonstrates no depedendency between variables, h(x)=x2=0. Solutions increment x-values by a conditional gradient, x_{n+1} = x_{n} + alpha*dx. Without dependency between x2 and x2 in the constraint, the constraint increments unequally by flag. 
  //           C) Start conditions. A Lagrange multipler in the book, lambda=lambda0+c*h(x), where lambda0 = 0, and h(x)=0 are zero. The system of equations has a linear equation with zeros. 
  //           D) Sometimes second derivatives in the Lagrangian have no solutions. A sublinear, linear, and superlinear case with absolutes generate zero denominators in the limit derivative, sometimes.

  //I skipped part b's solution because errata and tomorrow's log(Lagrangian) challenge.   
  
  float** M = makeMatrix(2);
  setMatrix(M,2);
  
  float* X = makeVector(2);
  setVector(X,2);
  
  float *b = makeVector(2);
  setVector(b,2);
  
  float **Am1 = makeMatrix (3);
  
  X[0]=0.1;
  X[1]=lambda0+c*h(x2);

  for(int i=0;;i++){
    M[0][0]=ddL(f,h,dF,dH,x1,x2,p,X[1]);
    M[0][1]=dH(h,x2);
    M[1][0]=dH(h,x2);
    M[1][1]=0;

    b[0]= dF(f,x1,x2,p)+X[1]*dH(h,x2);
    b[1] = h(x2);
    
    determinant = M[0][0]*M[1][1]-M[1][0]*M[0][1];
    if(determinant == 0){
      X[0]=b[0]/M[0][0];
      X[1]=lambda0+c*h(x2);
    } else{
      Am1 = inverseA(M);
      multiply(Am1,b,X,2,2,2);
    }
 
    dx = X[0];
    dlambda = X[1];

    alpha=lineMin(f,h,dF(f,x1,x2,p),x1,x2,p,dlambda);
    //New x1
    x1-=dx*dF(f,x1,x2,p);
    //New x2
    x2=0;
    //A solution check for convergence
    if(abs(alpha*dF(f,x1,x2,p))<precision){
      cout <<"Multiplier method with convergence factor (p = "<< p << "):" << endl;
     // cout <<"  Iteration total: " << i << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1:" << x1 << " x2: " << x2 << endl;
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
  RealFuncSecondDerivativeL ddL{computeSecondDerivativedL};
  
  float x1=1, x2=0, lambda0 = 0, p=1.5, precision = 10e-3;
  cout << endl << "Function f(x1,x2,p) = (1/2)(x1^2 + |x2|^p)+2*x2" << endl;
  cout <<"Constraint: x2 = 0" << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddL,x1,x2,p,lambda0,precision);

  p = 2;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial p: " << p << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddL,x1,x2,p,lambda0,precision);

  p = 3;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial p: " << p << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  evaluateMinimum(f,h,dF,dH,ddL,x1,x2,p,lambda0,precision);
  
  return 0; 
} 
