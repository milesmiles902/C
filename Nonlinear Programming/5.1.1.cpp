/*
Question 5.1.1:

Function: f(x1,x2,x3) = x1 + 2*x2 + 3*x3

Constraint: x1 + x2 + x3 = 1

            x>=0

a/b) The central path sketch contains a maximum bound of one to three-dimensions with a path from the initial conditions toward the boundary.

*/


//////////////////////////
//g++ 5.1.1.cpp -std=c++11
//////////////////////////

#include <functional>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

typedef function<float(float,float,float)> RealFunc;
typedef function<float(function<float(float,float,float)>,function<float(float,float,float)>,float,float,float)> RealFuncDerivative;

//Function: f(x)=x1+2*x2+3*x3
float Funcf(float x1, float x2, float x3){
  float val = (x1 + 2*x2 + 3*x3);
  return val;
}

//A constraint function: 1-x1-x2-x3
float Funcg(float x1, float x2, float x3){
  float val = (1-x1-x2-x3);
  return val;
}

//A function for computing a derivative
float computeDerivative(RealFunc f, RealFunc g, float x1, float x2, float x3){
  float h = sqrt(numeric_limits<float>::epsilon());
  float L = (f(x1+h,x2,x3)-f(x1,x2,x3))/h + (g(x1+h,x2,x3)-g(x1,x2,x3))/h     \
              + (f(x1,x2+h,x3)-f(x1,x2,x3))/h + (g(x1,x2+h,x3)-g(x1,x2,x3))/h  \
              + (f(x1,x2,x3+h)-f(x1,x2,x3))/h + (g(x1,x2,x3+h)-g(x1,x2,x3))/h;
  return L;
}

//Line minimization: https://en.wikipedia.org/wiki/Line_search
float lineMin(RealFunc f, RealFunc g, float d, float x1, float x2, float x3, float len){
  float x=0,h=0,alpha=0,idx=1,min=0;
      min=f(x1+alpha*d,x2+alpha*d,x3+alpha*d);
      for(int k=2;k<=len/100;k++){
        alpha+=len/100;
        h=f(x1+alpha*d,x2+alpha*d,x3+alpha*d) + g(x1+alpha*d,x2+alpha*d,x3+alpha*d);
        if(h<min){
          min=h;
          idx=k;
        }
      }
      return idx*len/100;
}

//A matrix display
void displayMatrix(float **matrix, int rows, int cols){
   cout << "The elements of the matrix are:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << " " << matrix[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

//A vector display
void displayVector(float* vector, int size){
    cout << "The elements of the vector are: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << vector[i] << " ";
    }
    cout << endl;
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

//A matrix[3x3] evaluator
float threebythreeDeterminant(float **A){
  float determinant = A[0][0] * ((A[1][1] * A[2][2]) - (A[1][2] * A[2][1]))
                        -   A[0][1] * ((A[1][0] * A[2][2]) - (A[1][2] * A[2][0]))
                        +   A[0][2] * ((A[1][0] * A[2][1]) - (A[1][1] * A[2][0]));
  return determinant;
}

//The inverse of a 3x3 matrix for the equation X=b*A^-1
float** inverseA(float** A){
  float** cofactor = makeMatrix(3);
  float** cofactor_transposed = makeMatrix(3);
  float** Am1 = makeMatrix(3);
  float** tempmatrix = makeMatrix(3);

  cofactor[0][0] =      twobytwoDeterminant(A[1][1], A[1][2], A[2][1], A[2][2]);
  cofactor[0][1] = -1 * twobytwoDeterminant(A[1][0], A[1][2], A[2][0], A[2][2]);
  cofactor[0][2] =      twobytwoDeterminant(A[1][0], A[1][1], A[2][0], A[2][1]);
  cofactor[1][0] = -1 * twobytwoDeterminant(A[0][1], A[0][2], A[2][1], A[2][2]);
  cofactor[1][1] =      twobytwoDeterminant(A[0][0], A[0][2], A[2][0], A[2][2]);
  cofactor[1][2] = -1 * twobytwoDeterminant(A[0][0], A[0][1], A[2][0], A[2][1]);
  cofactor[2][0] =      twobytwoDeterminant(A[0][1], A[0][2], A[1][1], A[1][2]);
  cofactor[2][1] = -1 * twobytwoDeterminant(A[0][0], A[0][2], A[1][0], A[1][2]);
  cofactor[2][2] =      twobytwoDeterminant(A[0][0], A[0][1], A[1][0], A[1][1]);


  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      cofactor_transposed[i][j]=cofactor[j][i];
    }
  }

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      tempmatrix[i][j] = cofactor_transposed[i][j]/threebythreeDeterminant(A);
    }
  }

  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      Am1[i][j] = tempmatrix[i][j];
    }
  }
  return Am1;
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

//A Short-step path-following method
void evaluateShort(RealFunc f, RealFunc g, RealFuncDerivative d, float x1, float x2, float x3, float smin, float smax, float n, float precision){
  float s=smin,len,dx,ds,dlambda,mu=1,lambda=0,alpha=0;
  float r1,r2,r3;
  
  float A[3] = {1,2,3};
  float S[3] = {0,0,0};

  float** M = makeMatrix(3);
  setMatrix(M,3);
  
  float *b = makeVector(3); 
  setVector(b,3);
  
  float *X = makeVector(3);
  setVector(X,3);

  float **Am1 = makeMatrix(3);

  X[0]=0;
  X[1]=1;
  X[2]=0;

  //The system of linear equations:
  //  |0 A I||dx     | = |-(Ax-b)         |
  //  |A 0 0||dlambda|   |-(A*lambda+S-c) |
  //  |S 0 X||ds     |   |-XS+s*mu        |
  //
  //  where S = matrix of slack variables
  //        A = coefficient matrix
  //        dlambda = Lagrange multiplier
  //        s = standard deviation
  //        mu = mean path
  //        X = variables
  //
  //An augmented matrix:
  //  |0 A      ||dlambda|=|-(A*lambda+S-c)      |
  //  |A -D^{-2}||dx     | |-(AX-b)+(-XS+s*mu)/X |
  //
  //  where D = sqrt(X/S)
  //        A = coefficient matrix
  //        dlambda = Lagrange multiplier
  //        s = standard deviation
  //        mu = mean path        
  //
  //Comparison:
  //
  //System of Linear Equations:            Augmented Matrix:
  //  -Gauss-Jordan Elimination[3x3]        -Cholesky Decomposition[2x2]
  //  -Slack variable[s]                    -Slack variable[s]
  //  -Lagrange System, multipler[lambda]   -Lagrange System, multiplier[lambda]
  //
  //  This function solves a system of linear equations with a pre-determined matrix size [3x3]. 
  //  The Lagrange equation has no initial solution because the constraint's initial conditions.  
  //  Literature defines this problem-type as "Infeasible start algorithms."
 
 
  for(int i=0;;i++){
    if(s<smin){
      s=smin;
    }else if(smin<s && s<smax){
      s = (1-smax/sqrt(n))*s;
    } else{
      s=smax;
    }

    M[0][1]=(A[0]+A[1]+A[2]);
    M[0][2]=1;
    M[1][0]=(A[0]+A[1]+A[2]);
    M[2][0]=(S[0]+S[1]+S[2]);
    M[2][2]=(X[0]+X[1]+X[2]);

    b[0] = -(x1+x2+x3-1);
    b[1] = -(lambda+2*lambda+3*lambda+S[0]+S[1]+S[2]);
    b[2] = -(s*mu-(x1*S[0]+x2*S[1]+x3*S[2]));

    Am1 = inverseA(M);
    multiply(Am1,b,X,3,3,3);
    
    dx = X[1];
    dlambda = X[2];
    ds = X[3];

    mu=(1-alpha*(1-s))*mu; //s*mu
    len=mu/(8*(smax*smax+n));
    alpha=1;
    lambda+=alpha*dlambda;
    s+=alpha*ds;

    S[0]=s;
    S[1]=s;
    S[2]=s;

    //New x1
    x1+=alpha*dx;
    //New x2
    x2+=alpha*dx;
    //New x3
    x3+=alpha*dx;

    //When x is less than zero
    if(x1<0){
      x1=0;
    } else if(x2<0){
      x2=0;
    } else if(x3<0){
      x3=0;
    }
    //A solution check for convergence
    if(abs(alpha*dx)<precision){
      cout <<"Short-step path-following method: " << endl << endl;
      cout <<"  Iteration total: " << i << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1:" << x1 << " x2: " << x2 << " x3: " << x3 << endl;
      cout << endl;
      return;
    } 
  }
  return;
}

//Long-step path-following method
void evaluateLong(RealFunc f, RealFunc g, RealFuncDerivative d, float x1, float x2, float x3, float smin, float smax, float n, float precision){
  float s=smin,len,dx,ds,dlambda,mu=1,lambda=0,alpha=0;
  float r1,r2,r3;
  
  float A[3] = {1,2,3};
  float S[3] = {0,0,0};

  float** M = makeMatrix(3);
  setMatrix(M,3);
  
  float *b = makeVector(3); 
  setVector(b,3);
  
  float *X = makeVector(3);
  setVector(X,3);

  float **Am1 = makeMatrix(3);

  X[0]=0;
  X[1]=1;
  X[2]=0;

  //The long-step method is a short-step path-following method, with s=s_{n-1}*mu and no line minimization. 
  //These algorithms "traverse" a constraint boundary in a Lagrangian system.
 
 
  for(int i=0;;i++){
    if(s<smin){
      s=smin;
    } else if(smin<s && s<smax) {
      s*=mu;
    } else {
      s=smax;
    }

    M[0][1]=(A[0]+A[1]+A[2]);
    M[0][2]=1;
    M[1][0]=(A[0]+A[1]+A[2]);
    M[2][0]=(S[0]+S[1]+S[2]);
    M[2][2]=(X[0]+X[1]+X[2]);

    b[0] = -(x1+x2+x3-1);
    b[1] = -(lambda+2*lambda+3*lambda+S[0]+S[1]+S[2]);
    b[2] = -(s*mu-(x1*S[0]+x2*S[1]+x3*S[2]));

    Am1 = inverseA(M);
    multiply(Am1,b,X,3,3,3);
    
    dx = X[1];
    dlambda = X[2];
    ds = X[3];

    mu=(1-alpha*(1-s))*mu; //s*mu
    len=mu/(8*(smax*smax+n));
    alpha=lineMin(f,g,dx,x1,x2,x3,len);
    lambda+=alpha*dlambda;
    s+=alpha*ds;

    S[0]=s;
    S[1]=s;
    S[2]=s;

    //New x1
    x1+=alpha*dx;
    //New x2
    x2+=alpha*dx;
    //New x3
    x3+=alpha*dx;

    //When x is less than zero
    if(x1<0){
      x1=0;
    } else if(x2<0){
      x2=0;
    } else if(x3<0){
      x3=0;
    }
    //A solution check for convergence
    if(abs(alpha*dx)<precision){
      cout <<"Long-step path-following method:" << endl << endl;
      cout <<"  Iteration total: " << i << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1:" << x1 << " x2: " << x2 << " x3: " << x3 << endl;
      cout << endl;
      return;
    } 
  }
  return;
}

//A Primal-dual Interior Point method
void evaluatePrimal(RealFunc f, RealFunc g, RealFuncDerivative d, float x1, float x2, float x3, float smin, float smax, float n, float precision){
  float s=smin,len,dx,ds,dlambda,mu=1,lambda=0,alpha=0;
  float r1,r2,r3;
  
  float A[3] = {1,2,3};
  float S[3] = {0,0,0};

  float** M = makeMatrix(3);
  setMatrix(M,3);
  
  float *b = makeVector(3); 
  setVector(b,3);
  
  float *X = makeVector(3);
  setVector(X,3);

  float **Am1 = makeMatrix(3);

  X[0]=0;
  X[1]=1;
  X[2]=0;

  //This method modifies a right-side equality (Ax=b) with less details in the slack equation.
  //These algorithms "traverse" a constraint boundary in a Lagrangian system.
 
 
  for(int i=0;;i++){
    if(s<smin){
      s=smin;
    } else if(smin<s && s<smax) {
      s*=mu;
    } else {
      s=smax;
    }

    M[0][1]=(A[0]+A[1]+A[2]);
    M[0][2]=1;
    M[1][0]=(A[0]+A[1]+A[2]);
    M[2][0]=(S[0]+S[1]+S[2]);
    M[2][2]=(X[0]+X[1]+X[2]);

    b[0] = 0;
    b[1] = 0;
    b[2] = (s*mu-(x1*S[0]+x2*S[1]+x3*S[2]));

    Am1 = inverseA(M);
    multiply(Am1,b,X,3,3,3);
    
    dx = X[1];
    dlambda = X[2];
    ds = X[3];

    mu=(1-alpha*(1-s))*mu; //s*mu
    len=mu/(8*(smax*smax+n));
    alpha=lineMin(f,g,dx,x1,x2,x3,len);
    lambda+=alpha*dlambda;
    s+=alpha*ds;

    S[0]=s;
    S[1]=s;
    S[2]=s;

    //New x1
    x1+=alpha*dx;
    //New x2
    x2+=alpha*dx;
    //New x3
    x3+=alpha*dx;

    //When x is less than zero
    if(x1<0){
      x1=0;
    } else if(x2<0){
      x2=0;
    } else if(x3<0){
      x3=0;
    }
    //A solution check for convergence
    if(abs(alpha*dx)<precision){
      cout <<"Primal-dual interior point method:" << endl;
      cout <<"  Iteration total: " << i << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1:" << x1 << " x2: " << x2 << " x3: " << x3 << endl;
      cout << endl;
      return;
    } 
  }
  return;
}

//A Predictor-Corrector Interior Point method
void evaluatePredictor(RealFunc f, RealFunc g, RealFuncDerivative d, float x1, float x2, float x3, float smin, float smax, float n, float precision){
  float s=smin,len,dx,ds,dlambda,mu=1,lambda=0,alpha=0;
  float r1,r2,r3;
  
  float A[3] = {1,2,3};
  float S[3] = {0,0,0};

  float** M = makeMatrix(3);
  setMatrix(M,3);
  
  float *b = makeVector(3); 
  setVector(b,3);
  
  float *X = makeVector(3);
  setVector(X,3);

  float **Am1 = makeMatrix(3);

  X[0]=0;
  X[1]=1;
  X[2]=0;

  //The method is akin to the long-step, short-step, and primal-dual equations, except slimmer;
 
  for(int i=0;;i++){
    if(s<smin){
      s=smin;
    } else if(smin<s && s<smax) {
      s*=mu;
    } else {
      s=smax;
    }

    M[0][1]=(A[0]+A[1]+A[2]);
    M[0][2]=1;
    M[1][0]=(A[0]+A[1]+A[2]);
    M[2][0]=(S[0]+S[1]+S[2]);
    M[2][2]=(X[0]+X[1]+X[2]);

    b[0] = 0;
    b[1] = 0;
    b[2] = (x1*S[0]+x2*S[1]+x3*S[2]);

    Am1 = inverseA(M);
    multiply(Am1,b,X,3,3,3);
    
    dx = X[1];
    dlambda = X[2];
    ds = X[3];

    mu=(1-alpha*(1-s))*mu; //s*mu
    len=mu/(8*(smax*smax+n));
    alpha=lineMin(f,g,dx,x1,x2,x3,len);
    lambda+=alpha*dlambda;
    s+=alpha*ds;

    S[0]=s;
    S[1]=s;
    S[2]=s;

    //New x1
    x1+=alpha*dx;
    //New x2
    x2+=alpha*dx;
    //New x3
    x3+=alpha*dx;

    //When x is less than zero
    if(x1<0){
      x1=0;
    } else if(x2<0){
      x2=0;
    } else if(x3<0){
      x3=0;
    }
    //A solution check for convergence
    if(abs(alpha*dx)<precision){
      cout <<"Predictor-corrector interior point method:" << endl;
      cout <<"  Iteration total: " << i << endl;
      cout <<"  Function Minimum x: " << setprecision(6) << "x1:" << x1 << " x2: " << x2 << " x3: " << x3 << endl;
      cout << endl;
      return;
    } 
  }
  return;
}

//The main with initial conditions
int main(){
  RealFunc f{Funcf};
  RealFunc g{Funcg};
  RealFuncDerivative d{computeDerivative};
  float x1=0.8, x2=0.15, x3=0.05, smin=0.1, smax=0.9, n=100, precision = 10e-6;

  cout <<"Function f(x1,x2,x3) = x1 + 2*x2 + 3*x3" << endl;
  cout <<"Constraint: x1 + x2 + x3 = 1" << endl;
  cout << endl;

  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial x3: " << x3 << endl;
  cout <<"Precision: " << precision << endl;
  cout << endl;

  //Short-step
  evaluateShort(f,g,d,x1,x2,x3,smin,smax,n,precision);
  //Long-step
  evaluateLong(f,g,d,x1,x2,x3,smin,smax,n,precision);
  //Primal-dual Interior Point
  evaluatePrimal(f,g,d,x1,x2,x3,smin,smax,n,precision); 
  //Predictor-corrector Variant
  evaluatePredictor(f,g,d,x1,x2,x3,smin,smax,n,precision);

  cout << "New initial conditions for x1, x2, and x3" << endl;
  x1=0.1;
  x2=0.2;
  x3=0.7;
  cout << endl;
  cout <<"Initial x1: " << x1 << endl;
  cout <<"Initial x2: " << x2 << endl;
  cout <<"Initial x3: " << x3 << endl;
  cout << endl;
  //Short-step path-following method:
  evaluateShort(f,g,d,x1,x2,x3,smin,smax,n,precision);
  //Long-step path-following method:
  evaluateLong(f,g,d,x1,x2,x3,smin,smax,n,precision);
  //Primal-dual interior point method:
  evaluatePrimal(f,g,d,x1,x2,x3,smin,smax,n,precision);
  //Preditor-corrector Variant
  evaluatePredictor(f,g,d,x1,x2,x3,smin,smax,n,precision);

  cout << "The initial conditions define an early convergence." << endl;
  cout << "Line minimization is also a reviewable factor." << endl;
  return 0; 
} 
