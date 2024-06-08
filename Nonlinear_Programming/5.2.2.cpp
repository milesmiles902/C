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
typedef function<float(function<float(function<float(float,float,float)>,float,float,float)>,float,float,float, float)> RealFuncSecondDerivativeL;

float FuncF(float x1, float x2, float p){
  float val = (x1*x1 + pow(abs(x2),p) )/2 + 2*x2;
  return val;
}

float FuncH(float x2){
  return x2;
}

float computeDerivativeF(RealFuncF f, float x1, float x2, float p){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (f(x1+h,x2,p)-f(x1,x2,p))/h + (f(x1,x2+h,p)-f(x1,x2,p))/h;
  return L;
}

float computeDerivativeH(RealFuncH h, float x2){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (h(x2+h)-h(x2))/h;
  return L;
}

float computeSecondDerivativedL(RealFuncDerivativeF df, RealFuncDerivativeH dH, float x1, float x2, float p, float lambda){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (df(x1+h,x2,p)-df(x1,x2,p))/h + (df(x1,x2+h,p)-df(x1,x2,p))/h + lambda*(dh(x2+h)-df(x2))/h;
  return L;
}

//Line minimization: https://en.wikipedia.org/wiki/Line_search
float lineMin(RealFunc f, float d, float x1, float x2, float p,float lambda){
  float x=0,h=0,alpha=0,idx=1,min=0;
      min=f(x1+alpha*d,x2+alpha*d,p)+lambda*x2;
      for(int k=2;k<=100;k++){
        alpha+=1/100;
        h=f(x1+alpha*d,x2+alpha*d,p) + lambda*x2;
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
  float** cofactor = makeMatrix(2);
  float** cofactor_transposed = makeMatrix(2);
  float** Am1 = makeMatrix(2);
  float** tempmatrix = makeMatrix(2);

  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      cofactor_transposed[i][j]=cofactor[j][i];
    } 
  }
  
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      tempmatrix[i][j] = cofactor_transposed[i][j]/twobytwoDeterminant(cofactor_transposed[0][0],cofactor_transposed[0][1],cofactor_transposed[1][0],cofactor_transposed[1][1]);
    }
  }
  
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      Am1[i][j] = tempmatrix[i][j];
    }
  }
  return Am1;
}

void evaluateMinimum(RealFuncF f, RealFuncH h, RealFuncDerivativeF dF,RealFuncDerivativeH dH,RealFuncSecondDerivativeL ddL, float x1, float x2, float p, float lambda0, float precision){
  float dx=0, alpha=1, dlambda=lambda0;
  
  
  float** M = makeMatrix(2);
  setMatrix(M,2);
  
  float** X = makeVector(2);
  setVector(X,2);
  
  float *b = makeVector(2);
  setVector(b,2);
  
  float **Am1 = makeMatrix (3);
  
  X[0]=dx;
  X[1]=lambda0+c*h(x2)-lambda

  for(int i=0;;i++){
    lambda=lambda0+c*h(x2);
    M[0][0]=ddL(df,dh,x1,x2,p)
    M[0][1]=dH(x2);
    M[1][0]=dH(x2);
    M[1][1]=-1/lambda;
    
    b[0]= -([df(x1,x2,p)-df(dx,dx,p)]+[[lambda0+c*h(x2)-lambda]+lambda0_c*h(x2)]*(dh(x2)-dh(dx))+[lambda0+c*h(x2)-lambda]*dh(x2))
    b[1] = (lambda0+c*h(x2)-lambda0)/c-(dH(x2)-dH(dx));
    
    Am1 = inverseA(M);
    multiply(Am1,b,X,2,2,2);
    
    dx = X[1];
    dlambda = X[2];
    ds = X[3];
    
    alpha=lineMin(f,d(f,x1,x2,p),x1,x2,p,dlambda);
    dlambda+=x2;
    //New x1
    x1+=alpha*d(f,x1,x2,p);
    //New x2
    x2+=0;

    //A solution check for convergence
    if(abs(alpha*d(f,x1,x2,p))<precision){
      cout <<"Multiplier method with convergence factor (p = "<< p << "):" << endl;
      cout <<"  Iteration total: " << i << endl;
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
  RealFuncSecondDerivativeL ddL{computeSecondDerivativeL};
  
  float x1=0.8, x2=0, lambda0 = 0, p=1.5, precision = 10e-6;
  cout << endl << "Function f(x1,x2,x3) = (1/2)(x1^2 + x2^2)+2*x2" << endl;
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
