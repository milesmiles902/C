##Not Complete: Redo
/*
 * @file .cpp
 * @Description Train a multilayer perceptron neural network for multiclass classification with
 *              backpropagation logistic activation function is used.
 * @Eqns #5.10 z=h[sum w*z)]
 *       #5.113 z=h[sum(w*z+w0)]
 *       #5.66 delJ=(1-z^2)*sum(w*delK)
 *       #5.67 delT/delw=delJ*x, delE/delw=delK*z
 *       #5.43 w_{t+1}=w_{t}-eta*delE(w_{t})
 */

#include "nr3.h"
#include "print.cpp"
#include <cmath>
#include <iostream>

/*
 *Input:
 * X(dxn): Data matrix
 * Y(1xn): Label vector
 * k(Tx1): Number of hidden nodes
 * lambda: Regularization parameter
 *Output:
 * model: Print model structure
 * L: (regularized cross entropy) loss
 */

void mlpClass(MatDoub X, VecDoub y, VecDoub k, int lambda){
  int i,j,T,iter,maxiter,xrows,xcols,ysize,ksize;
  Doub eta,tol,err,Wn,dW,sum,db;
  eta=1e-3;
  tol=1e-4;
  maxiter=50000;
  T=k.size()-1;
  ysize=y.size();
  VecDoub L(maxiter), W(T), b(T), R(T), Z(T+1), Y(ysize);
  xrows=X.nrows();
  xcols=X.ncols();
  
  for(i=0;i<k.size();i++){
    W[i]=rand()%5;
    b[i]=rand()%5;
  }
  std::cout << "W: ";
  printVector(W);
  std::cout << "b: ";
  printVector(b);

  Y=y;
  L[0]=1;
  for(iter=0;iter<maxiter;iter++){ 
    VecDoub func(T);
    for(i=0;i<T;i++){
      func[i]=W[i]*Z[i]+b[i];
    }
    std::cout << "func: ";
    printVector(func);
    
    for(i=0;i<T-1;i++){
      Z[i+1]=1/(1+exp(func[i]));
    }
    std::cout << "Z: ";
    printVector(Z);

    for(i=0;i<T;i++){
      sum+=exp(func[i]);
    }
    std::cout << "sum: " << sum << std::endl;;
    
    Z[T]=exp(func[T-1])/(1+sum);
    
    std::cout << "Z: ";
    printVector(Z);
    
    err=Z[T+1];
    std::cout << "err: " << err << std::endl;
    for(i=0;i<T;i++){
      Wn+=W[i]*W[i];
    }
    std::cout << "err: " << err << std::endl;
    std::cout << "Wn: " << Wn << std::endl;
    for(i=0;i<ysize;i++){
      L[iter]=-Y[i]*log(err)+0.5*lambda*Wn;
      std::cout << "L[iter]: " << L[iter] << std::endl;
      //std::cout << "L[iter-1]: " << L[iter-1] << std::endl;
      if (abs(L[iter]-L[iter-1]) < tol*L[iter-1]) return;
    }   
    for(i=0;i<T;i++){
      R[i]=Z[T]-Y[i];
    }
    std::cout << "R[T]: " << R[T-1] << std::endl;
    for(i=T-1;i>=0;i--){
      R[i-1]=Z[i]*(1-Z[i])*W[i]*R[i];
    }
    std::cout << "R: ";
    printVector(R);

    for(i=0;i<T;i++){
      dW=Z[i]*R[i]+lambda*W[i];
      for(j=0;j<T;j++) {
        db+=R[j];
      };
      W[i]=W[i]-eta*dW;
      b[i]=b[i]-eta*db;
    }
    std::cout << "dW: " << dW << std::endl;
    for(i=0;i<iter;i++){
      //L[i]=L[i];
    } 
    std::cout << "W: ";
    printVector(W);
    std::cout << "b: ";
    printVector(b);
    //Seems to crash upon no convergence.
  }
}

int main(){
  Int i,j,n,m,T,lambda;
  n=3;
  m=3;
  T=3;
  MatDoub X(m,n);
  VecDoub y(n), k(T);
  
  lambda=2;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
    y[i]=rand()%10;
  } 
  mlpClass(X,y,k,lambda);
}
